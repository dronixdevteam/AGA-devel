/*********************************************************************
 * webcam_server                                                     *
 *                                                                   *
 * (c) 2002 Donn Morrison donn@donn.dyndns.org                       *
 *                                                                   *
 * code used from Gerd Knorr's xawtv (libng)                         *
 * - and -                                                           *
 * Cory Lueninghoener's gqcam                                        *
 *                                                                   *
 *    waits for connections from a viewer and sends                  *
 *    jpeg encoded captures as a live video feed                     *
 *                                                                   *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <linux/videodev.h>

#include "client.h"
#include "webcam_server.h"
#include "imgqueue.h"
#include "version.h"

#define MAX_READ_LEN		1024	/* max client socket read length (bytes) */
#define READ_TIMEOUT		15	/* client socket read timeout before disconnect (seconds) */
#define MAX_OLD_IMAGES		20	/* max old images before disconnect */

/*-----------------------------------------------------------
  client types
  -----------------------------------------------------------*/
#define WCS_CLIENT_TYPE_BAD	-1
#define WCS_CLIENT_TYPE_UNKNOWN	0
#define WCS_CLIENT_TYPE_APPLET	1
#define WCS_CLIENT_TYPE_HTTP	2
#define WCS_CLIENT_TYPE_ADMIN	3

/*-----------------------------------------------------------
  match_client_type:
  - parses the client request and matches the type and version
  
  a client request should resemble the following:
  HTTP:        GET / HTTP/1.1
  WCS APPLET:  GET / WCS/0.40
  WCS ADMIN:   GET / ADMIN/0.40
  -----------------------------------------------------------*/

int match_client_type(char *data, char *tag, char *version)
{
	char *ptr;
	char *beg = data;
        char *tmpnull = NULL;
	char tmpchar = 0;
	int res = -1;

        /* get end of first line and work backwards looking for
           the last space. once this is found, check the client tag and
           version which will proceed the last '/',
        */
        ptr = (char *)strchr(data, '\r');
	if(!ptr)
	        ptr = (char *)strchr(data, '\n');
        if(!ptr)
        {
                ptr = data + strlen(data);
        }
        else
        {
                tmpnull = ptr;
		tmpchar = *tmpnull;
                *tmpnull = '\0';
        }

        while(*ptr != ' ' && ptr > beg)
                ptr--;
	
	ptr = (char *)strstr(ptr, tag);
	if(ptr)
	{
		if(version)
		{
        		ptr = (char *)strchr(ptr, '/');
        		if(ptr)
        		{
				if(*(ptr+1))
					ptr++;
				if(strcmp(ptr, version) == 0)
				{
					res = 0;
				}
        		}
		}
		else
			res = 0;
	}
	if(tmpnull)
               *tmpnull = tmpchar;
        return res;
}

int get_client_type(struct caminfo *cam, char *buffer)
{
	if(match_client_type(buffer, "WCS", get_version()) == 0)
		return WCS_CLIENT_TYPE_APPLET;
	else if(match_client_type(buffer, "HTTP", NULL) == 0)
		return WCS_CLIENT_TYPE_HTTP;
/* ** currently not implemented
	else if(match_client_type(buffer, "ADMIN", get_version()) == 0)
		return WCS_CLIENT_TYPE_ADMIN;
*/
	return -1;
}

/* ** currently not implemented
int match_admin_password(char *buffer, char *password)
{
	char *ptr;
	
	ptr = (char *)strchr(buffer, '\n');
	if(ptr)
	{
		if(*(ptr+1))
			ptr++;
		if(strstr(ptr, password))
			return 0;
	}
	return -1;
}

int handle_admin_connection(struct caminfo *cam, struct connection *con, char *request)
{
	char logmsg[512];
	if(match_admin_password(request, cam->o.admin_pw) < 0)
	{
		sprintf(logmsg, "%s attempted admin access with bad password\n", inet_ntoa(con->remote_addr.sin_addr));
		log(cam, logmsg);
		return -1;
	}

	return 0;
}
*/

int check_limits(struct caminfo *cam, struct connection *con)
{
	time_t current;
	
	/* max bytes */
	if(cam->o.max_stream_bytes && con->total_bytes >= cam->o.max_stream_bytes)
		return -1;

	/* max seconds */
	time(&current);
	if(cam->o.max_stream_seconds && con->start && ((current - con->start) >= cam->o.max_stream_seconds))
		return -1;

	/* max frames */
	if(cam->o.max_stream_frames && con->total_frames >= cam->o.max_stream_frames)
		return -1;

	return 0;
}

/*-----------------------------------------------------------
  handle_connection
  - waits for a client request, gets and sends latest
    image from queue, loops
  - does some connection accounting
  -----------------------------------------------------------*/
int handle_connection(struct connection *con)
{
	struct caminfo *cam = con->cam;
	struct imagequeue *ptr;
	long len, res;
	char buffer[MAX_READ_LEN+1];
	char logmsg[512];
	int got_request = 0;

	con->total_bytes = 0;
	con->total_frames = 0;
	con->id_last = 0;
	con->old_images = 0;
	con->client_type = 0;
	con->start = 0;
	con->end = 0;

	while(1)
	{
		res = 1;
		
		/* check if we've passed our per connection limits */
		if(check_limits(cam, con) < 0)
			break;

		/* if got_request == 1 here, we've already got a request, but no images were available
		   so we sleep and loop until we find one */
		if(!got_request)
		{
			struct timeval tv;
			fd_set rfds;
			tv.tv_sec = READ_TIMEOUT;
			tv.tv_usec = 0;

			FD_ZERO(&rfds);
			FD_SET(con->socketfd, &rfds);

			/* wait for client request */
			if(!select(con->socketfd+1, &rfds, 0, 0, &tv) || !FD_ISSET(con->socketfd, &rfds))
				break;

			len = recv(con->socketfd, &buffer, MAX_READ_LEN, 0);
			if(len < 1)
				break;
			buffer[len] = 0;
			
			/* determine client type */
			if(!con->client_type)
			{
				con->client_type = get_client_type(cam, buffer);
			}
			if(con->client_type == WCS_CLIENT_TYPE_BAD)
				break;

			/* check if we allow http connections */
			if(con->client_type == WCS_CLIENT_TYPE_HTTP && !cam->o.allow_http)
			{
				con->client_type = WCS_CLIENT_TYPE_BAD;
				sprintf(buffer, "HTTP/1.0 403 Forbidden\nContent-type: text/html\nConnection: close\nServer: webcam_server %s\n\n\n<h1>Forbidden</h1>webcam_server %s: HTTP connections have been disabled on this server.\n", get_version(), get_version());
				send(con->socketfd, buffer, strlen(buffer),0);
				break;
			}
			
			/* check if we allow admin connections */
/* ** currently not implemented
			if(con->client_type == WCS_CLIENT_TYPE_ADMIN && !cam->o.allow_admin)
			{
				con->client_type = WCS_CLIENT_TYPE_BAD;
				break;
			}
*/

			got_request = 1;
		}

		/* do the following only once per connection */
		if(con->start == 0)
		{
			char *client = NULL;
			/* someone has connected, inform the grabber thread */
			sem_post(&cam->sem_con);

			/* get start time */
			time(&con->start);
			pthread_mutex_lock(&cam->lock_info);
			cam->s.num_users++;
			pthread_mutex_unlock(&cam->lock_info);
			
			switch(con->client_type)
			{
				case WCS_CLIENT_TYPE_APPLET:
					client = "WCS APPLET";
					break;
				case WCS_CLIENT_TYPE_HTTP:
					client = "HTTP";
					break;
				case WCS_CLIENT_TYPE_ADMIN:
					client = "ADMIN APPLET";
					break;
			}

			sprintf(logmsg, "%s connected via %s\n", inet_ntoa(con->remote_addr.sin_addr), client);
			log(cam, logmsg);
		}

		/* if admin client, pass off to handler */
/* ** currently not implemented
		if(con->client_type == WCS_CLIENT_TYPE_ADMIN)
		{
			handle_admin_connection(cam, con, buffer);
			break;
		}
*/

		/* get the latest image */
		pthread_mutex_lock(&cam->lock_queue);
		ptr = peek(cam);
		if(!ptr)
		{
			pthread_mutex_unlock(&cam->lock_queue);
			usleep(100000);
			continue;
		}
		pthread_mutex_lock(&ptr->lock_ref);
		ptr->ref++;
		pthread_mutex_unlock(&ptr->lock_ref);

		pthread_mutex_unlock(&cam->lock_queue);

		/* don't send the same image more than once */
		if(ptr->id != con->id_last)
		{
			/* send response header */
			if(con->client_type == WCS_CLIENT_TYPE_HTTP)
				sprintf(buffer, "HTTP/1.0 200 OK\nContent-type: image/jpeg\nContent-Length: %d\nConnection: close\n\n", ptr->len);
			else
				sprintf(buffer, "WCS/%s 200 OK\nContent-type: image/jpeg\nContent-Length: %d\nConnection: close\n\n", get_version(), ptr->len);
			if(send(con->socketfd, buffer, strlen(buffer),0) != strlen(buffer))
				res = 0;

			/* send jpeg */
			if(res && send(con->socketfd, ptr->jpeg_data, ptr->len, 0) != ptr->len)
				res = 0;

			con->total_bytes += ptr->len;
			con->total_frames++;
			con->id_last = ptr->id;
			con->old_images = 0;
			got_request = 0;
			
			/* check if we've disabled streaming */
			if(!cam->o.allow_stream)
				break;
		}
		else
		{
			/* no new image...wait a while and try again */
			usleep(100000);
			con->old_images++;
			if(con->old_images == MAX_OLD_IMAGES)
			{
				/* too many old images */
				pthread_mutex_lock(&ptr->lock_ref);
				ptr->ref--;
				pthread_mutex_unlock(&ptr->lock_ref);
				break;
			}
		}

		pthread_mutex_lock(&ptr->lock_ref);
		ptr->ref--;
		pthread_mutex_unlock(&ptr->lock_ref);

		if(con->client_type == WCS_CLIENT_TYPE_HTTP)
			break;

		if(!res)
			break;
	}
	if(con->client_type > 0) 
	{

		/* get end time */
		time(&con->end);

		sprintf(logmsg, "%s disconnected, %d seconds, %ld bytes, %.2f Kbytes/second, %ld frames, %.2f fps\n",
			inet_ntoa(con->remote_addr.sin_addr),		/* address */
			(int)(con->end - con->start),			/* seconds */
			con->total_bytes,				/* bytes */
			(float)((con->total_bytes/1024.0)/((con->end - con->start) ? con->end - con->start : 1)),/* Kbytes/sec */
			con->total_frames,				/* frames */
			(float)((float)con->total_frames/((float)(con->end - con->start) ? con->end - con->start : 1)));/* frames/sec */
		log(cam,logmsg);

		pthread_mutex_lock(&cam->lock_info);
		cam->s.num_users--;
		pthread_mutex_unlock(&cam->lock_info);

		/* someone has disconnected, inform the grabber thread */
		sem_wait(&cam->sem_con);
	}

	close(con->socketfd);
	free(con);
	return 0;
}

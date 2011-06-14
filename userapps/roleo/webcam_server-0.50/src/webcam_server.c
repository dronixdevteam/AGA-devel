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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <linux/videodev.h>
#include <semaphore.h>
#include <sys/ioctl.h>

#include "webcam_server.h"
#include "grabber.h"
//#include "watchdog.h"
#include "client.h"
#include "version.h"
#include "camera.h"
#include "unpalette.h"

#define DEBUG 0
void print_rgb(char * hdr, struct RGB x) { printf("rgb:%s = %d,%d,%d\n", hdr,x.r&0xFF,x.g&0xFF,x.b&0xFF); }

/*-----------------------------------------------------------
  default options
  -----------------------------------------------------------*/
#define DEF_PORT		8888
#define DEF_QUALITY		60
#define DEF_CAMDEVFILE		"/dev/video0"
#define DEF_LOGFILE		"/var/log/webcam_server.log"
#define DEF_CAPTION		"%Y-%m-%d %H:%M:%S" /* strftime */
#define DEF_WIDTH		320
#define DEF_HEIGHT		240
#define DEF_RETRYINIT		0
#define DEF_DAEMON		0
#define DEF_SWAPRGB		0
#define DEF_TESTFPS		0
#define DEF_FLIP_HORIZ		0
#define DEF_FLIP_VERT		0
#define DEF_GAMMA		0
#define DEF_TEXT_FG		{0,0,0}
#define DEF_TEXT_BG		{255,255,255}
#define DEF_TRANS		{128,0,128}
#define DEF_TEXT_XPOS		0	
#define DEF_TEXT_YPOS		0
#define DEF_ROTATE		0
#define DEF_FORCE_READ		0
#define DEF_ALLOW_HTTP		1
#define DEF_ALLOW_STREAM	1
#define DEF_MAX_STREAM_BYTES	0
#define DEF_MAX_STREAM_SECONDS	0
#define DEF_MAX_STREAM_FRAMES	0
/* ** currently not implemented
#define DEF_ALLOW_ADMIN		0
#define DEF_ADMIN_PW		"\0"
*/
#define DEF_PALETTE		-1

char *str_replace(const char *str, const char *find, const char *replace)
{
	char *ptr,*ret;
	int found=0;
	ptr = (char*)str;

	while((ptr=strstr(ptr, find)))
	{
		char *start,*end;
		int slen,elen,rlen,flen;

		rlen = strlen(replace);
		flen = strlen(find);
		slen = ptr - str;
		elen = strlen(ptr)-flen;

		start = (char*)malloc(slen+1);
		strncpy(start, str, slen);
		start[slen]=0;
		
		end = (char*)malloc(elen+1);
		strncpy(end, ptr+flen, elen);
		end[elen]=0;

		ret = (char*)malloc(slen+elen+rlen+1);
		sprintf(ret, "%s%s%s", start, replace, end);

		free(start);
		free(end);

		ptr = ret;

		found=1;
	}

	if(!found)
	{
		ret = (char*)malloc(strlen(str)+1);
		strcpy(ret, str);
	}

	return ret;
}

/*-----------------------------------------------------------
  create_and_listen
  - creates a server socket and listens
  - its a seperate function to clean up main
  -----------------------------------------------------------*/
int create_and_listen(int port)
{
	int sockfd, yes=1;
	struct sockaddr_in addr;
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return -1;
	}
	
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
	{
		perror("setsockopt");
		return -1;
	}
	
	if(bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind");
		return -1;
	}
	
	if(listen(sockfd, 5) < 0)
	{
		perror("listen");
		return -1;
	}
	
	return sockfd;
}

/*-----------------------------------------------------------
  log
  - opens a logfile for appending on first call
  - subsequent calls write to the open logfile and/or stdout
  -----------------------------------------------------------*/
void log(struct caminfo *cam, char *text)
{
	static int tried = 0;
	static int dups = 0;
	time_t      t;
	struct tm  *tm;
	char date[128];
	static char *last_msg = NULL;

	if(!tried)
	{
		/* open log file */
		cam->log = fopen(cam->o.logfile, "a");
		if(cam->log == NULL)
		{
			fprintf(stderr, "could not open logfile '%s' for writing\n", cam->o.logfile);
		}
		tried = 1;
	}
	
	time(&t);
	tm = localtime(&t);
	strftime(date,127,"%Y-%m-%d %H:%M:%S",tm);
	
	if(last_msg)
	{
		if(strcmp(last_msg, text) == 0)
		{
			dups++;
			return;
		}
		else
		{
			free(last_msg);
			last_msg = NULL;
		}
	}

	/* write the message to stdout and/or logfile */
	pthread_mutex_lock(&cam->lock_log);
	if(cam->o.verbose)
	{
		if(dups > 0)
		{
			fprintf(stdout, "%s [%s] log: the last message repeated %d times\n", date, cam->o.devfile, dups);
		}
		
		fprintf(stdout, "%s [%s] %s", date, cam->o.devfile, text);
		fflush(stdout);
	}
		
	if(cam->log)
	{
		if(dups > 0)
		{
			fprintf(cam->log, "%s [%s] log: the last message repeated %d times\n", date, cam->o.devfile, dups);
		}
		fprintf(cam->log, "%s [%s] %s", date, cam->o.devfile, text);
		fflush(cam->log);
	}
	pthread_mutex_unlock(&cam->lock_log);
	
	if(!last_msg)
	{
		last_msg = (char *)malloc(strlen(text)+1);
		strcpy(last_msg, text);
		dups = 0;
	}
}

/*-----------------------------------------------------------
  usage, parse_args
  - highly complex, undocumented functions used for encrypting
    and secretly displaying or parsing various portions of text
  -----------------------------------------------------------*/
void usage()
{
printf("webcam_server %s, copyright 2001-2004 Donn Morrison\n\n", get_version());
printf("usage: webcam_server [options]\n\n\
     option             description [default value]\n\n\
     -a                 - test mode (fps) [no]\n\
     -c \"caption\"       - caption text [%%Y-%%m-%%d %%H:%%M:%%S], \"\" for none\n\
     -d video_device    - v4l compliant device [/dev/video]\n\
     -Ds                - disable stream support [no]\n\
     -Dh                - disable http support [no]\n\
     -fh		- flip image horizontally\n\
     -fv		- flip image vertically\n\
     -g geometry        - change default geometry (WIDTHxHEIGHT) [320x240]\n\
     -G gamma		- gamma correction (-100-100) [0]\n\
     -h                 - this help screen\n\
     -l logfile         - log to file [/var/log/webcam_server.log]\n\
     -mb                - maximum bytes per connection [0 (disabled)]\n\
     -ms                - maximum seconds per connection [0 (disabled)]\n\
     -mf                - maximum frames per connection [0 (disabled)]\n\
     -n                 - force use of read() system call, rather than mmap\n\
     -p tcp_port        - tcp listen port [8888]\n\
     -q jpeg_quality    - jpeg compression quality (0-100) [60]\n\
     -r                 - if camera init fails, retry forever [no]\n\
     -R value           - rotate image value*90 degrees CCW (0-3) [0]\n\
     -s                 - daemon mode [no]\n\
     -tf R,G,B          - text forground colour [255,255,255]\n\
     -tb R,G,B          - text background colour [0,0,0]\n\
     -tt R,G,B          - transparency colour [128,0,128]\n\
                          (set -tf or -tb to this to make transparent)\n\
     -T x,y             - xy-position of text [0,0]\n\
     -v                 - verbose [no]\n\
     -x                 - swap RGB -> BGR [no]\n\
\n");

/* ** currently not implemented
     -Ea                - enable admin support [no]\n\
     -e password        - set admin password [null]\n\
     -P                 - force palette n (videodev.h) [off]\n\
*/
}

int parse_args(struct caminfo *cam, int argc, char *argv[])
{
	int res = 0, i;
	for(i=1; i<argc; i++)
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1])
			{
			case 'h':
			case '-':
				usage();
				return -1;
			case 'p':
				if(i+1 < argc)
					cam->o.port = atoi(argv[++i]);
				else
					res = -1;
				break;
			case 'd':
				if(i+1 < argc)
					cam->o.devfile = argv[++i];
				else
					res = -1;
				break;
			case 'c':
				if(i+1 < argc)
					cam->o.caption = argv[++i];
				else
					res = -1;
				break;
			case 'v':
				cam->o.verbose = 1;
				break;

			case 'r':
				cam->o.retry_init = 1;
				break;
			case 's':
				cam->o.daemon = 1;
				break;
			case 'q':
				if(i+1 < argc)
					cam->o.jpeg_quality = atoi(argv[++i]);
				else
					res = -1;
				break;
				/*
			case 'P':
				if(i+1 < argc)
					cam->o.palette = atoi(argv[++i]);
				else
					res = -1;
				break;
				*/
			case 'x':
				cam->o.swap_rgb = 1;
				break;
			case 'f':
				switch(argv[i][2])
				{
					case 'h':
						cam->o.flip_horiz = 1;
						break;
					case 'v':
						cam->o.flip_vert = 1;
						break;
				}
				break;
			case 'T':
				{
					if(i+1 < argc)
					{
						int x,y;
						sscanf(argv[++i], "%d,%d", &x,&y);
						cam->o.text_xpos = x;
						cam->o.text_ypos = y;

						printf("text xy = %d,%d\n", x,y);
					}
					else
						res = -1;

				}
				break;
			case 't':
				switch(argv[i][2])
				{
					case 'f':
						if(i+1 < argc)
						{
							int r,g,b;
							sscanf(argv[++i], "%d,%d,%d", &r,
							                              &g,
										      &b);
							cam->o.text_fg.r = r;
							cam->o.text_fg.g = g;
							cam->o.text_fg.b = b;
						}
						else
							res = -1;
						break;
					case 'b':
						if(i+1 < argc)
						{
							int r,g,b;
							sscanf(argv[++i], "%d,%d,%d", &r,
							                              &g,
										      &b);
							cam->o.text_bg.r = r;
							cam->o.text_bg.g = g;
							cam->o.text_bg.b = b;
						}
						else
							res = -1;
						break;
					case 't':
						if(i+1 < argc)
						{
							int r,g,b;
							sscanf(argv[++i], "%d,%d,%d", &r,
							                              &g,
										      &b);
							cam->o.trans.r = r;
							cam->o.trans.g = g;
							cam->o.trans.b = b;
						}
						else
							res = -1;
						break;
					default:
						res = -1;
				}
				break;
			case 'D':
				switch(argv[i][2])
				{
					case 'h':
						cam->o.allow_http = 0;
						break;
					case 's':
						cam->o.allow_stream = 0;
						break;
					default:
						res = -1;
				}
				break;
/* ** currently not implemented
			case 'E':
				switch(argv[i][2])
				{
					case 'a':
						cam->o.allow_admin = 1;
						break;
					default:
						res = -1;
				}
				break;
			case 'e':
				if(i+1 < argc)
					cam->o.admin_pw = argv[++i];
				else
					res = -1;
				break;
*/
			case 'm':
				if(i+1 < argc)
				switch(argv[i][2])
				{
					case 'b':
						cam->o.max_stream_bytes = atoi(argv[++i]);
						break;
					case 's':
						cam->o.max_stream_seconds = atoi(argv[++i]);
						break;
					case 'f':
						cam->o.max_stream_frames = atoi(argv[++i]);
						break;
					default:
						res = -1;
				}
				else
					res = -1;
				break;
			case 'a':
				cam->o.test_fps = 1;
				break;
			case 'n':
				cam->o.use_read = 1;
				break;
			case 'l':
				if(i+1 < argc)
					cam->o.logfile = argv[++i];
				else
					res = -1;
				break;
			case 'R':
				if(i+1 < argc)
					cam->o.rotate = atoi(argv[++i]);
				else
					res = -1;
				break;
			case 'g':
				if(i+1 < argc)
				{
					int w=0,h=0;
					
					if(strchr(argv[i+1], 'x') == NULL)
					{
						res = -1;
						break;
					}
					
					sscanf(argv[++i], "%dx%d", &w, &h);

					if(w < 1 || h < 1 || w > 2048 || h > 2048)
					{
						fprintf(stderr, "invalid width, height: %dx%d. using defaults: %dx%d\n",
						       w,h,DEF_WIDTH,DEF_HEIGHT);
						cam->o.width = DEF_WIDTH;
						cam->o.height = DEF_HEIGHT;
					}

					cam->o.width = w;
					cam->o.height = h;
				}
				else
					res = -1;
				break;
			case 'G':
				if(i+1 < argc)
				{
					cam->o.gamma = atoi(argv[++i]);
				}
				else
					res = -1;
				break;
			default:
				res = -1;
				break;
			};
		}
		else
		{
			res = -1;
		}

		if(res == -1)
		{
			fprintf(stderr, "invalid option or missing parameter: %s\n", argv[i]);
			return res;
		}
	}
	
	return res;
}

int main(int argc, char *argv[])
{
	int sockfd=0, clientfd;
	struct sockaddr_in remote_addr;
	socklen_t addr_len;
	pthread_t pt;
	struct caminfo *cam;
	struct connection *con;
	int res;
	
	cam = (struct caminfo *)malloc(sizeof(struct caminfo));
	if(!cam)
	{
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	cam->mmap = NULL;

	/* ignore broken pipes n stuff */
	signal(SIGPIPE, SIG_IGN);
	signal(SIGALRM, SIG_IGN);

	/* init mutexes */
	pthread_mutex_init(&cam->lock_queue, NULL);
	pthread_mutex_init(&cam->lock_info, NULL);
	pthread_mutex_init(&cam->lock_id, NULL);
	pthread_mutex_init(&cam->lock_log, NULL);
	sem_init(&cam->sem_con, 0, 0);

	/* defaults */
	cam->o.caption = DEF_CAPTION;
	cam->o.devfile = DEF_CAMDEVFILE;
	cam->o.port = DEF_PORT;
	cam->o.jpeg_quality = DEF_QUALITY;
	cam->o.retry_init = DEF_RETRYINIT;
	cam->o.daemon = DEF_DAEMON;
	cam->o.swap_rgb = DEF_SWAPRGB;
	cam->o.test_fps = DEF_TESTFPS;
	cam->o.width = DEF_WIDTH;
	cam->o.height = DEF_HEIGHT;
	cam->o.logfile = DEF_LOGFILE;
	cam->o.flip_horiz = DEF_FLIP_HORIZ;
	cam->o.flip_vert = DEF_FLIP_VERT;
	cam->o.gamma = DEF_GAMMA;
	struct RGB fg = DEF_TEXT_FG;
	struct RGB bg = DEF_TEXT_BG;
	struct RGB trans = DEF_TRANS;
	cam->o.text_fg = fg;
	cam->o.text_bg = bg;
	cam->o.trans = trans;
	cam->o.text_xpos = DEF_TEXT_XPOS;
	cam->o.text_ypos = DEF_TEXT_YPOS;
	cam->o.rotate = DEF_ROTATE;
	cam->o.use_read = DEF_FORCE_READ;
	cam->o.allow_http = DEF_ALLOW_HTTP;
	cam->o.allow_stream = DEF_ALLOW_STREAM;
	cam->o.max_stream_bytes = DEF_MAX_STREAM_BYTES;
	cam->o.max_stream_seconds = DEF_MAX_STREAM_SECONDS;
	cam->o.max_stream_frames = DEF_MAX_STREAM_FRAMES;
/* ** currently not implemented
	cam->o.admin_pw = DEF_ADMIN_PW;
	cam->o.allow_admin = DEF_ALLOW_ADMIN;
*/
	cam->o.palette = DEF_PALETTE;

	/* overwrite defaults with command line args */
	if(parse_args(cam, argc, argv) < 0)
		exit(1);

	/* don't do this stuff if we're in test mode */
	if(!cam->o.test_fps)
	{
		/* create listening socket */
		sockfd = create_and_listen(cam->o.port);
		if(sockfd < 1)
			exit(1);

		/* go into daemon mode if told to */	
		if(cam->o.daemon)
			if(daemon(0,0) < 0)
			{
				fprintf(stderr, "daemon failed.\n");
				exit(1);
			}
	}
	
	/* open camera device...retry infinitely if told to */
	res = open_cam(cam, cam->o.devfile);
	
	while(res < 0 && cam->o.retry_init)
	{
		usleep(5000000);
		fprintf(stderr, "camera init failed, retrying...\n");
		res = open_cam(cam, cam->o.devfile);
	}
	if(res < 0)
	{
		fprintf(stderr, "unable to initialise camera\n");
		exit(1);
	}

	/* get camera defaults */
	get_cam_info(cam);
	cam->vid_win.width = cam->o.width;
	cam->vid_win.height = cam->o.height;
	if(set_cam_info(cam) < 0)
	{
		fprintf(stderr, "error setting video device parameters, using defaults\n");
		get_cam_info(cam);
		if(set_cam_info(cam) < 0)
		{
			fprintf(stderr, "not a valid video device? quitting.\n");
			exit(1);
		}
	}
	cam->o.width = cam->vid_win.width;
	cam->o.height = cam->vid_win.height;
	
	{
		/*if(cam->o.palette != -1)
		{
			/* force use of certain palette */
		/*	cam->vid_pic.palette = cam->o.palette;
			ioctl(cam->dev, VIDIOCSPICT, &cam->vid_pic);
			ioctl(cam->dev, VIDIOCGPICT, &cam->vid_pic);
			if(cam->vid_pic.palette == cam->o.palette)
			{
				printf("using palette %d\n", cam->o.palette);
			}
			else
			{
				printf("could not set palette to %d\n", cam->o.palette);
			}
		}
		else
		{
	*/	
		/* check for a valid colour palette */
		int palfound = 0;
		int brightness = -1, hue = -1, colour = -1, contrast = -1, whiteness = -1;
		for(cam->pal = palettes; cam->pal->val >= 0; cam->pal++)
		{
			if(cam->o.palette != -1)
			{
				if(cam->pal->val != cam->o.palette)
					continue;
				else
					cam->vid_pic.palette = cam->pal->val;
			}
			else
			{
				cam->vid_pic.palette = cam->pal->val;
			}
			cam->vid_pic.depth = cam->pal->depth;
			if(brightness >= 0) cam->vid_pic.brightness = brightness;
			if(hue >= 0) cam->vid_pic.hue = hue;
			if(colour >= 0) cam->vid_pic.colour = colour;
			if(contrast >= 0) cam->vid_pic.contrast = contrast;
			if(whiteness >= 0) cam->vid_pic.whiteness = whiteness;

			ioctl(cam->dev, VIDIOCSPICT, &cam->vid_pic);
			ioctl(cam->dev, VIDIOCGPICT, &cam->vid_pic);
			if(cam->vid_pic.palette == cam->pal->val)
			{
//				printf("using palette %d\n", cam->pal->val);
				palfound = 1;
				break;
			}
		}
		if(!palfound)
		{
			fprintf(stderr, "No supported colour palette found.\n");
			return 1;
		}

	}

	cam->grab_thread_alive = 1;
	pthread_create(&cam->pt_grab, NULL, (void*)grab_thread, (void *)cam);

	/* start the watchdog thread */
	/*
	pthread_create(&pt, NULL, (void*)watchdog_thread, (void *)cam);
	pthread_detach(pt);
*/
	if(cam->o.test_fps)
	{
		pthread_join(cam->pt_grab, NULL);
		exit(0);
	}
	else
	{
		pthread_detach(cam->pt_grab);
	}

	log(cam, "webcam_server started\n");

	addr_len = sizeof(remote_addr);

	while((clientfd = accept(sockfd, (struct sockaddr *)&remote_addr, &addr_len)) > 0)
	{
		/* con is free'd at end of handle_connection */
		con = (struct connection*)malloc(sizeof(struct connection));
		con->cam = cam;

		/* get connection info */
		con->socketfd = clientfd;
		memcpy(&con->remote_addr, &remote_addr, addr_len);

		/* handle the connection */
		pthread_create(&pt, NULL, (void*)handle_connection, (void*)con);
		pthread_detach(pt);
	}
	
	close(sockfd);
	return 0;
}

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
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <linux/videodev.h>

#include "webcam_server.h"
#include "grabber.h"
#include "client.h"
#include "camera.h"
#include "imgqueue.h"

#define MAX_WATCHDOG_RETRIES	5	/* max watchdog retries */

/*-----------------------------------------------------------
  watchdog_thread
  - simulates a client connection and ensures the grabber
    thread is working. this is a quick hack to unstick
    dead read()s
  -----------------------------------------------------------*/
int watchdog_thread(struct caminfo *cam)
{
	struct imagequeue *ptr;
	int last_id = -1;
	int tries = 0;
	int res;
	char buff[256];
	
	while(1)
	{
		/* simulate a client connection */
		sem_post(&cam->sem_con);
		
		/* get the latest image */
		pthread_mutex_lock(&cam->lock_queue);
		ptr = peek(cam);
		if(!ptr)
		{
			/* no images available */
			pthread_mutex_unlock(&cam->lock_queue);
		}
		else
		{
			pthread_mutex_lock(&ptr->lock_ref);
			ptr->ref++;
			pthread_mutex_unlock(&ptr->lock_ref);

			pthread_mutex_unlock(&cam->lock_queue);

			if(ptr->id == last_id)
			{
				/* hmm...same id as last time */
				tries++;
				sprintf(buff,"watchdog: image (%d) was the same as last time! %d/%d\n",
					last_id, tries, MAX_WATCHDOG_RETRIES);
				log(cam,buff);
			}
			else
			{
				last_id = ptr->id;
				tries = 0;
			}
			
			pthread_mutex_lock(&ptr->lock_ref);
			ptr->ref--;
			pthread_mutex_unlock(&ptr->lock_ref);
		}
		
		if(tries == MAX_WATCHDOG_RETRIES)
		{
			log(cam,"watchdog: ERROR: grabber thread suspected stuck\n");
			/* drastic action!
			 * we assume the grabber thread is stuck
			 * on a read, and we kill it, reinit the
			 * camera, and restart the grabber thread
			 */
			tries = 0;
			last_id = -1;
			
			log(cam,"watchdog: killing grabber thread\n");
			pthread_cancel(cam->pt_grab);
			
			usleep(1000000);
			
			log(cam,"watchdog: closing camera\n");
			if(close_cam(cam) > -1)			
				log(cam,"watchdog: camera closed\n");
			usleep(5000000);
			
			log(cam,"watchdog: re-initing camera\n");
			res = open_cam(cam, cam->o.devfile);
			
			while(res < 0 && cam->o.retry_init)
			{
				log(cam,"watchdog: re-init failed, retrying\n");
				usleep(1000000);
				res = open_cam(cam, cam->o.devfile);
			}

			if(res < 0)
			{
				log(cam,"watchdog: re-init failed, exiting\n");
				exit(1);
			}

			sprintf(buff, "watchdog: re-init ok: %d\n", res);
			log(cam,buff);
			
			log(cam,"watchdog: setting camera defaults\n");
			/* get camera defaults */
			get_cam_info(cam);
			cam->vid_win.width = cam->o.width;
			cam->vid_win.height = cam->o.height;
			if(set_cam_info(cam) < 0)
			{
				get_cam_info(cam);
				if(set_cam_info(cam) < 0)
				{
					exit(1);
				}
			}
			cam->o.width = cam->vid_win.width;
			cam->o.height = cam->vid_win.height;
			
			log(cam,"watchdog: restarting grab_thread\n");
			cam->grab_thread_alive = 1;
			pthread_create(&cam->pt_grab, NULL, (void*)grab_thread, (void *)cam);
			pthread_detach(cam->pt_grab);
		}
		
		sem_wait(&cam->sem_con);
		
		/* sleep and then check again */
		usleep(2000000);
	}
}

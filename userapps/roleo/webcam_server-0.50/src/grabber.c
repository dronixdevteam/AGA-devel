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
#include <sys/timeb.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <unistd.h>
#include <linux/videodev.h>

#include "webcam_server.h"
#include "imgqueue.h"
#include "filters.h"
#include "camera.h"
#include "unpalette.h"

#define MAX_BAD_GRABS		10	/* max bad image captures before exit */
#define CAPTURE_PAUSE		75000	/*  pause for 75ms between captures */

// MALLOC_CHECK_=1

/*-----------------------------------------------------------
  grab_thread
  - runs only when clients are connected or when test mode
    enabled
  - captures an image, converts it to jpeg, pushes it on 
    queue, loops
  -----------------------------------------------------------*/
int grab_thread(struct caminfo *cam)
{
	char *jpeg_data = NULL;
	int jpeg_len = 0;
	struct imagequeue *new;
	struct image *img = NULL, *tmp = NULL;

	u_long frames=0;
	time_t t0;
	time_t t1;
	struct timeb start_time;
	struct timeb stop_time;
	unsigned int capture_time;
	
	time(&t0);
	while(cam->grab_thread_alive)
	{
		if(cam->s.bad_grabs == MAX_BAD_GRABS)
			break;
	
		if(!cam->o.test_fps)
		{
			/* wait for a connection */
			sem_wait(&cam->sem_con);
			sem_post(&cam->sem_con);
		}

		ftime(&start_time);
		
		/* fetch an image */
		img = get_cam_image(cam);
		if(img == NULL)
		{
#if DEBUG
			fprintf(stderr,"bad image grab (%d of %d)\n", cam->s.bad_grabs, MAX_BAD_GRABS);
			usleep(100000);
			cam->s.bad_grabs++;
#endif
			continue;
		}
		cam->s.bad_grabs = 0;
		
		time(&t1);
		if(cam->o.test_fps)
		{
			float fps;
			/* test mode only */
			frames++;
			fps = (float)frames/((t1 - t0) ? t1-t0 : 1.0);
			printf("read a frame: %d bytes, fps = %.3f, frames = %ld\n", img->bufsize, fps, frames);
			continue;
		}

		/* convert to rgb24 */
		tmp = image_new(img->width, img->height);
		cam->pal->routine(tmp, img->buf);
		img = tmp;

		/* swap rgb? */
		if(cam->o.swap_rgb)
			swap_rgb24(img);
		
		/* adjust gamma? */
		if(cam->o.gamma)
			adjust_gamma(img, cam->o.gamma);

		/* flip horiz/vert */
		if(cam->o.flip_horiz)
			fliph(img);
		if(cam->o.flip_vert)
			flipv(img);

		/* rotate image? */
		if(cam->o.rotate > 0)
			rotate_image(img, cam->o.rotate);

		/* add the caption? */
		if(cam->o.caption && strlen(cam->o.caption) > 0)
		{
			char *text,*tmp;
			char viewers[16], frames[16], version[16];
			int x,y;
			snprintf(viewers, 15, "%d", cam->s.num_users);
			snprintf(frames, 15, "%d", cam->s.id_newest_img);
			snprintf(version, 15, "%s", get_version());
			
			tmp = str_replace(cam->o.caption, "%%v", viewers);
			text = str_replace(tmp, "%%f", frames);
			free(tmp);
			tmp = str_replace(text, "%%V", version);
			free(text);
			text = tmp;

			x = 50;
			y = 20;
			add_text(img, text, cam->o.text_fg, cam->o.text_bg, cam->o.trans, cam->o.text_xpos, cam->o.text_ypos);
			free(text);
		}
		
		/* allocate some storage for the new image */
		new = (struct imagequeue *)malloc(sizeof(struct imagequeue));
		if(!new)
		{
			perror("malloc");
			clean(cam);
			continue;
		}
		
		/* compress the image in jpeg format */
		jpeg_len = image2jpeg(img, &jpeg_data, cam->o.jpeg_quality);
		
		image_delete(tmp);
		free(tmp);

		pthread_mutex_lock(&cam->lock_queue);
		pthread_mutex_lock(&cam->lock_id);

		/* set fields */
		new->id = ++(cam->s.id_newest_img);
		new->len = jpeg_len;
		new->jpeg_data = jpeg_data;
		new->ref = 0;
		new->next = NULL;
		pthread_mutex_init(&new->lock_ref, NULL);
	
		/* put it on the queue */
		push(cam, new);
		
		pthread_mutex_unlock(&cam->lock_id);

		/* calculate optimum capture rate to save CPU time */
		ftime(&stop_time);
		capture_time = (stop_time.time - start_time.time);
		if (capture_time == 0)
		{
			capture_time = stop_time.millitm - start_time.millitm;
		}
		else
		{
			capture_time *= 1000;
			capture_time += (stop_time.millitm - start_time.millitm);
		}
		capture_time *= 100;
		if (capture_time < CAPTURE_PAUSE)
			usleep(CAPTURE_PAUSE - capture_time);

		/* clear unused images from the queue */
		clean(cam);
		pthread_mutex_unlock(&cam->lock_queue);
	}
	
	fprintf(stderr,"grab thread exiting...\n");

	munmap(cam->mmap, cam->vid_mbuf.size);

	exit(1);
}

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
#include <semaphore.h>
#include <linux/videodev.h>

#include "webcam_server.h"
#include "imgqueue.h"

/*-----------------------------------------------------------
  imagequeue procedures
  
  push: appends a fresh image to the queue
  clean: removes unreferenced (old) images
  peek: retrieves the newest image in the queue
        without removing it
  -----------------------------------------------------------*/
void push(struct caminfo *cam, struct imagequeue *new)
{
	struct imagequeue *ptr;
	int count = 0;

	ptr = cam->queue;
	while(ptr)
	{
		if(ptr->next == NULL)
			break;
		ptr = ptr->next;
		count++;
	}

	if(ptr)
	{
		ptr->next = new;
		new->prev = ptr;
	}
	else
	{
		cam->queue = new;
		new->prev = NULL;
	}
}

int clean(struct caminfo *cam)
{
	struct imagequeue *ptr, *tmp;
	int count = 0;

	ptr = cam->queue;
	while(ptr)
	{
		tmp = ptr->next;
		/* only remove it if its not being used and its not the latest */
		pthread_mutex_lock(&ptr->lock_ref);
		if(ptr->ref == 0 && ptr->id != cam->s.id_newest_img)
		{
			if(ptr == cam->queue)
				cam->queue = tmp;
			if(ptr->prev)
				ptr->prev->next = ptr->next;
			if(ptr->next)
				ptr->next->prev = ptr->prev;
			free(ptr->jpeg_data);
			pthread_mutex_unlock(&ptr->lock_ref);
			pthread_mutex_destroy(&ptr->lock_ref);
			free(ptr);
			count++;
		}
		else
			pthread_mutex_unlock(&ptr->lock_ref);
		
		ptr = tmp;
	}
	
	return count;
}

struct imagequeue *peek(struct caminfo *cam)
{
	struct imagequeue *ptr;
	int count = 0, id;

	pthread_mutex_lock(&cam->lock_id);
	id = cam->s.id_newest_img;
	pthread_mutex_unlock(&cam->lock_id);

	ptr = cam->queue;
	while(ptr)
	{
		if(ptr->id == id)
			break;
		ptr = ptr->next;
		count++;
	}
	
	return ptr;
}

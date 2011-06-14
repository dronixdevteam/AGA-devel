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

#ifndef _IMGQUEUE_H_INCLUDED_
#define _IMGQUEUE_H_INCLUDED_

#include <pthread.h>

struct imagequeue *peek(struct caminfo *cam);
int clean(struct caminfo *cam);
void push(struct caminfo *cam, struct imagequeue *new);

struct imagequeue
{
	int id;
	int ref;
	pthread_mutex_t lock_ref;
	char *jpeg_data;
	int len;
	struct imagequeue *next;
	struct imagequeue *prev;
};

#endif

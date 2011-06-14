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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
//#include <linux/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <linux/videodev.h>

#include "webcam_server.h"
#include "camera.h"
#include "image.h"

/*-----------------------------------------------------------
  camera procedures
  
  open_cam: attempts to open a camera's device file
  close_cam: pretty obvious
  get_cam_info/set_cam_info: get/set camera attributes
  get_cam_image: get an image from the camera, returns NULL if failed
  -----------------------------------------------------------*/
int open_cam(struct caminfo *cam, char *devfile)
{
	if(!devfile)
		return -1;
	/* initialize and open camera */
	cam->dev = open(devfile, O_RDONLY);
	if(cam->dev < 0)
	{
		char msg[256];
		sprintf(msg, "%s", devfile);
		perror(msg);
	}
	return cam->dev;
}

int close_cam(struct caminfo *cam)
{
	return close(cam->dev);
}

int set_cam_info(struct caminfo *cam)
{
	if (ioctl (cam->dev, VIDIOCSPICT, &cam->vid_pic) == -1) {
		perror ("ioctl (VIDIOCSPICT)");
		return -1;
	}
	cam->vid_win.flags = 0;
	if (ioctl (cam->dev, VIDIOCSWIN, &cam->vid_win) == -1) {
		perror ("ioctl (VIDIOCSWIN)");
		return -1;
	}
	return 0;
}

void get_cam_info(struct caminfo *cam)
{
	if(ioctl(cam->dev, VIDIOCGCAP, &cam->vid_caps) != 0)
	{
		perror("ioctl (VIDIOCGCAP)");
		return;
	}
	if(ioctl(cam->dev, VIDIOCGWIN, &cam->vid_win) != 0)
	{
		perror("ioctl (VIDIOCGCAP)");
		return;
	}
	if(ioctl(cam->dev, VIDIOCGPICT, &cam->vid_pic) != 0)
	{
		perror("ioctl (VIDIOCGCAP)");
		return;
	}
	if(ioctl(cam->dev, VIDIOCGMBUF, &cam->vid_mbuf) == 0)
	{
		if(!cam->mmap)
			cam->mmap = mmap(0, cam->vid_mbuf.size, PROT_READ, MAP_SHARED, cam->dev, 0);
		if(cam->mmap == MAP_FAILED)
			cam->o.use_read = 1;
		else
		{
//			cam->o.use_read = 0;
		}
	}
	else
	{
		cam->o.use_read = 1;
	}
}

struct image *get_cam_image(struct caminfo *cam)
{
	static struct image *img = NULL;
	int len = 0;

	if(cam->o.use_read)
	{
		if(img == NULL)
		{
			img = image_new(cam->o.width, cam->o.height);

			if(img == NULL)
			{
				perror("malloc: get_cam_image()");
				return NULL;
			}
		}

		/* read an image from camera */
		len = read(cam->dev, img->buf, img->bufsize);
		
		if(len != img->bufsize)
			printf("get_cam_image(): len != img->bufsize, just letting you know\n");

		if(len <= 0)
			return NULL;
	}
	else
	{
		int res;

		img = (struct image*)malloc(sizeof(struct image));
		img->width = cam->o.width;
		img->height = cam->o.height;
		img->bufsize = img->width * img->height * 3;
		img->buf = NULL;
		
		cam->vid_v4lmmap.format = cam->pal->val;
		cam->vid_v4lmmap.frame = 0;
		cam->vid_v4lmmap.width = cam->o.width;
		cam->vid_v4lmmap.height = cam->o.height;
		
		/* read an image from camera */
		res = ioctl(cam->dev, VIDIOCMCAPTURE, &cam->vid_v4lmmap);
		if(res != 0)
			return NULL;

		res = ioctl(cam->dev, VIDIOCSYNC, &cam->vid_v4lmmap);
		if(res != 0)
			return NULL;

		img->buf = cam->mmap;
	}
	
	return img;
}

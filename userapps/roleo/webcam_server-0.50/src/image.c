#include <stdio.h>
#include "image.h"

struct image *image_new(int width, int height)
{
	struct image *img = (struct image*)malloc(sizeof(struct image));
	if(img)
	{
		img->width = width;
		img->height = height;
		img->bufsize = width*height*3;
		img->buf = (char *)malloc(img->bufsize);
		if(!img->bufsize)
		{
			free(img);
			img = NULL;
		}
	}
	
	return img;
}

void image_delete(struct image *img)
{
	free(img->buf);
}

#ifndef _IMAGE_H_INCLUDED_
#define _IMAGE_H_INCLUDED_

struct image
{
	int bufsize;
	int width, height;
	unsigned char *buf;
};


struct RGB
{
	char r;
	char g;
	char b;
};

struct image *image_new(int width, int height);
void image_delete(struct image *img);

#endif

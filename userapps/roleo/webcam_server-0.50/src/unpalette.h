#ifndef _UNPALETTE_H_
#define _UNPALETTE_H_

/* $Id: unpalette.h,v 1.3 2004/09/28 06:58:53 donn Exp $ */

struct image;

/* Converts an image from some palette into rgb24 format.
 * The image struct contains width and height of the image,
 * as well as a large enough output buffer.
 */
typedef void unpalettizer(struct image *, unsigned char *);

/* Array of all known palettes and their conversion routines */
struct palette
{
	int val;
	unpalettizer *routine;
	double bpp;	/* bytes per pixel, can be something like 1.5, in which case
	             * the number of input bytes must be a multiple of 2. */
	int depth;
	char *name;
};
extern struct palette palettes[];

/* TODO: make this extensible with plugins? */

#endif


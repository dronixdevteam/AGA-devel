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
#include <semaphore.h>
#include <jpeglib.h>
#include <jerror.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <linux/videodev.h>

#include "webcam_server.h"
#include "filters.h"
#include "jdatabuf.h"

#define COMPARE_RGB(x,y) ((x.r == y.r && x.g == y.g && x.b == y.b))

/*-----------------------------------------------------------
  image processing procedures
  
  image2jpeg: encodes raw image to jpeg
  add_text: adds a caption to the image
  swap_rgb24: RGB->RBG
  fliph: flips the image horizontally
  flipv: flips vertically
  -----------------------------------------------------------*/
int image2jpeg(struct image *img, char **jpeg_data, int quality)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	int i, size;
	int w, h;
	unsigned char *line;
	
	w = img->width;
	h = img->height;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_buff_dest(&cinfo);
	cinfo.image_width = w;
	cinfo.image_height = h;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);
	jpeg_start_compress(&cinfo, TRUE);
	for (i = 0, line = img->buf; i < h; i++, line += w*3)
		jpeg_write_scanlines(&cinfo, &line, 1);
	jpeg_finish_compress(&cinfo);
	
	size = get_jpeg_size(&cinfo);
	
	/* this memory must be freed elsewhere */
	(*jpeg_data) = (char *)malloc(size);
	if(!(*jpeg_data))
	{
		jpeg_destroy_compress(&cinfo);
		jpeg_buff_free(&cinfo);
		return -1;
	}
	memcpy(*jpeg_data, ((my_dest_ptr)cinfo.dest)->buffer, size);

	jpeg_destroy_compress(&cinfo);
	jpeg_buff_free(&cinfo);
	
	return size;
}

/* Gerd Knorr */

#define CHAR_HEIGHT  11
#define CHAR_WIDTH   6
#define CHAR_START   4
#include "font_6x11.h"

void add_text(struct image *img, char *text, struct RGB fg, struct RGB bg, struct RGB trans, int xpos, int ypos)
{
	time_t      t;
	struct tm  *tm;
	char        *line,*ptr,prepend[32];
	int         i,x,y,f,len,size,numlines,textwidth,textheight;
	int width = img->width;
	int height = img->height;

	size = strlen(text) +
	       128 +			/* 128 for strftime and null */
	       height/CHAR_HEIGHT;	/* total lines space in image */
	
	line = (char *)malloc(size);
	if(!line)
		return;

	time(&t);
	tm = localtime(&t);
	len = strftime(line,size-1,text,tm);

	numlines = strlen(line) / ((width-xpos)/CHAR_WIDTH) + (strlen(line)%((width-xpos)/CHAR_WIDTH) ? 1 : 0);
	textwidth = strlen(line)*CHAR_WIDTH;
	textheight = numlines*CHAR_HEIGHT;

	//printf("textwidth = %d textheight=%d\n", textwidth,textheight);
	if(xpos + textwidth > img->width || ypos + textheight > img->height)
	{
		// trim the text somehow or just don't draw it
		//printf("text is too big\n");
	}

	/* Colour the background 
	if(bg.r != trans.r && bg.g != trans.g && bg.b != trans.b)
	{
		for (y = 0; y < CHAR_HEIGHT; y++) {
			numlines = strlen(line) / (width/CHAR_WIDTH) + (strlen(line)%(width/CHAR_WIDTH) ? 1 : 0);
			ptr = img->buf + (3 * width * (height-CHAR_HEIGHT-4 - ((numlines-1) * CHAR_HEIGHT) +y+1)) + 12;
			for (x = 0; x < len; x++) {
				if(x % ((width/CHAR_WIDTH)-1) == 0 && x > 0)
				{
					numlines --;
					ptr = img->buf + (3 * width * (height-CHAR_HEIGHT-4 - ((numlines-1) * CHAR_HEIGHT) +y+1)) + 12;
				}
				for (i = CHAR_WIDTH-1; i >= 0; i--) {
					ptr[0] = bg.r;
					ptr[1] = bg.g;
					ptr[2] = bg.b;
					ptr += 3;
				}
			}
		}
	}*/

	numlines = 1;
	ptr = line;
	while((ptr = strstr(ptr, "\\n")))
	{
		numlines++;
	}

	//printf("numlines -> %d\n", numlines);
	
	/* Draw the text */
	for (y = 0; y < CHAR_HEIGHT; y++) {
		int textpos;
//		numlines = strlen(line) / ((width-xpos)/CHAR_WIDTH) + (strlen(line)%((width-xpos)/CHAR_WIDTH) ? 1 : 0);
//		printf("numlines=%d\n", numlines);
		textpos = (3*ypos*width + y*3*width) + (3*xpos);
		if(textpos > 3*width*height)
		{
//			printf("the text is too large\n");
			break;
		}
		ptr = img->buf + textpos;
		for (x = 0; x < len; x++) {
			if(line[x] == '\\' && x+1 < len && line[x+1] == 'n')
			{
				//printf("found a newline\n");
			}
			/*
			if(line[x] x % ((width/CHAR_WIDTH)-1) == 0 && x > 0)
			{
				numlines --;
//				ptr = img->buf + 3 * width * (height-CHAR_HEIGHT-2 - ((numlines-1) * CHAR_HEIGHT) +y) + 12;
				ptr = img->buf + 3*xpos*ypos;
			}*/
			f = fontdata[line[x] * CHAR_HEIGHT + y];
			for(i=0; i<CHAR_WIDTH; i++) {
				if(xpos + x*CHAR_WIDTH + i >= width)
					break;
				if (f & (CHAR_START << CHAR_WIDTH-1-i)) {
					if(!COMPARE_RGB(fg, trans))
					{
						ptr[0] = fg.r;
						ptr[1] = fg.g;
						ptr[2] = fg.b;
					}
				}
				else
				{
					if(!COMPARE_RGB(bg, trans))
					{
						ptr[0] = bg.r;
						ptr[1] = bg.g;
						ptr[2] = bg.b;
					}
				}
				ptr += 3;
			}
		}
	}
	free(line);
}

void swap_rgb24(struct image* img)
{
        char  c;
        char *p = img->buf;
        int   i = img->bufsize/3;

        while (--i) {
                c = p[0]; p[0] = p[2]; p[2] = c;
                p += 3;
        }
}

void adjust_gamma(struct image* img, int corr)
{
	int i=img->bufsize;
	char *p = img->buf;
	while(--i)
	{
		if(corr > 0)
		{
			if(p[0] + corr <= 255)
				p[0] += corr;
			else
				p[0] = 255;
		}
		else
		{
			if(p[0] + corr >= 0)
				p[0] += corr;
			else
				p[0] = 0;
		}
		p++;
	}
}

void rotate_image(struct image *img, int rot)
{
    static unsigned char * rotimg = NULL;
    char *in = img->buf;
    int wp, hp;
    int top=0, left=0, bottom, right;

    int i, j;

    int w = img->width;
    int ow = img->width;
    int oh = img->height;

    if (rotimg == NULL && (rotimg = (char*)malloc(ow*oh*3)) == NULL ) {
        perror("rotate_image()");
	return;
    }
    switch ( rot ) {
    default:
    case 0:
	for (j = 0; j < oh; j++) {
	    int ir = (j+top)*w+left;
	    int or = j*ow;
	    for (i = 0; i < ow; i++) {
		rotimg[3*(or + i)]   = in[3*(ir+i)];
		rotimg[3*(or + i)+1] = in[3*(ir+i)+1];
		rotimg[3*(or + i)+2] = in[3*(ir+i)+2];
	    }
	}
	wp = ow;
	hp = oh;
	break;
    case 1:
	for (i = 0; i < ow; i++) {
	    int rr = (ow-1-i)*oh;
	    int ic = i+left;
	    for (j = 0; j < oh; j++) {
		rotimg[3*(rr+j)]   = in[3*((j+top)*w+ic)];
		rotimg[3*(rr+j)+1] = in[3*((j+top)*w+ic)+1];
		rotimg[3*(rr+j)+2] = in[3*((j+top)*w+ic)+2];
	    }
	}
	wp = oh;
	hp = ow;
	break;
    case 2:
	for (j = 0; j < oh; j++) {
	    int ir = (j+top)*w;
	    for (i = 0; i < ow; i++) {
		rotimg[3*((oh-1-j)*ow + (ow-1-i))] = in[3*(ir+i+left)];
		rotimg[3*((oh-1-j)*ow + (ow-1-i))+1] = in[3*(ir+i+left)+1];
		rotimg[3*((oh-1-j)*ow + (ow-1-i))+2] = in[3*(ir+i+left)+2];
	    }
	}
	wp = ow;
	hp = oh;
	break;
    case 3:
	for (i = 0; i < ow; i++) {
	    int rr = i*oh;
	    int ic = i+left;
	    rr += oh-1;
	    for (j = 0; j < oh; j++) {
		rotimg[3*(rr-j)]   = in[3*((j+top)*w+ic)];
		rotimg[3*(rr-j)+1] = in[3*((j+top)*w+ic)+1];
		rotimg[3*(rr-j)+2] = in[3*((j+top)*w+ic)+2];
	    }
	}
	wp = oh;
	hp = ow;
	break;
    }
    memcpy(in, rotimg, ow*oh*3);
    img->width = wp;
    img->height = hp;
}

int compare_images(unsigned char *last, unsigned char *current, int width, int height)
{
    unsigned char *p1 = last;
    unsigned char *p2 = current;
    int avg, diff, max, i = width*height*3;

    for (max = 0, avg = 0; --i; p1++,p2++) {
	diff = (*p1 < *p2) ? (*p2 - *p1) : (*p1 - *p2);
	avg += diff;
	if (diff > max)
	    max = diff;
    }
    avg = avg / width / height;
    fprintf(stderr,"compare: max=%d,avg=%d\n",max,avg);
    /* return avg */
    return max;
}

void fliph(struct image *img)
{
	int i,j;
	char *dest = NULL;
	char *srcline, *destline;

	dest = (char *)malloc(img->width * img->height * 3);
	if(!dest)
		return;

	for(i=0;i<img->height;i++)
	{
		srcline = img->buf + i*3*img->width;
		destline = dest + i*3*img->width + 3*(img->width-1);
		for(j=0;j<img->width;j++)
		{
			memcpy(destline, srcline, 3);
			srcline += 3;
			destline -= 3;
		}
	}

	memcpy(img->buf, dest, img->width * img->height * 3);
	free(dest);
}

void flipv(struct image *img)
{
	int i;
	char *dest = NULL;
	char *srcline, *destline;
	
	dest = (char *)malloc(img->width * img->height * 3);
	if(!dest)
		return;
	
	for(i=0;i<img->height;i++)
	{
		srcline = img->buf + i*img->width*3;
		destline = dest + (img->height-i)*img->width*3 - img->width*3;
		memcpy(destline, srcline, img->width*3);
	}
	
	memcpy(img->buf, dest, img->width * img->height * 3);
	free(dest);
}

#include <stdio.h>
#include <sys/types.h>
#include <linux/videodev.h>

#include "unpalette.h"
#include "image.h"

static unsigned char citb(int);

static unpalettizer unpalette_yuv420p;
static unpalettizer unpalette_rgb24;
static unpalettizer unpalette_bgr24;
static unpalettizer unpalette_rgb32;
static unpalettizer unpalette_bgr32;
static unpalettizer unpalette_grey;
static unpalettizer unpalette_yuyv;
static unpalettizer unpalette_yuv420;
static unpalettizer unpalette_rgb565;
static unpalettizer unpalette_rgb555;

struct palette palettes[] =
{
	{ VIDEO_PALETTE_RGB24,			unpalette_bgr24,		3,		24,	"bgr24"							},
	{ VIDEO_PALETTE_RGB24 | 0x80,	unpalette_rgb24,		3,		24,	"rgb24"							},
	{ VIDEO_PALETTE_RGB32,			unpalette_bgr32,		4,		32,	"bgr32"							},
	{ VIDEO_PALETTE_RGB32 | 0x80,	unpalette_rgb32,		4,		32,	"rgb32"							},
	{ VIDEO_PALETTE_YUYV,			unpalette_yuyv,		2,		24,	"yuyv (16 bpp)"				},
	{ VIDEO_PALETTE_YUV422,			unpalette_yuyv,		2,		24,	"yuv422 (16 bpp)"				},
	{ VIDEO_PALETTE_RGB565,			unpalette_rgb565,		2,		16,	"rgb565"							},
	{ VIDEO_PALETTE_RGB555,			unpalette_rgb555,		2,		15,	"rgb555"							},
	{ VIDEO_PALETTE_YUV420P,		unpalette_yuv420p,	1.5,	24,	"yuv420 planar (12 bpp)"	},
	{ VIDEO_PALETTE_YUV420,			unpalette_yuv420,		1.5,	24,	"yuv420 (12 bpp)"				},
	{ VIDEO_PALETTE_GREY,			unpalette_grey,		1,		8,		"grayscale (8 bpp)"			},
	{ -1 }
};

static
unsigned char
citb(int i)
{
	if (i >= 256)
		return 255;
	if (i < 0)
		return 0;
	return i;
}

static
void
unpalette_yuv420p(struct image *dst, unsigned char *src)
{
	const unsigned char *u, *v, *bu, *bv;
	unsigned char *dstbuf;
	unsigned int dx, dy, uvc, buvc;
	
	u = src + dst->width * dst->height;
	v = u + (dst->width / 2) * (dst->height / 2);
	dstbuf = dst->buf;
	
	buvc = 0;
	for (dy = 0; dy < dst->height; dy++)
	{
		bu = u;
		bv = v;
		uvc = 0;
		
		for (dx = 0; dx < dst->width; dx++)
		{
			/**dstbuf++ = citb((int) *src + 1.4075 * ((int) *v - 128));
			*dstbuf++ = citb((int) *src - 0.3455 * ((int) *u - 128) - 0.7169 * ((int) *v - 128));
			*dstbuf++ = citb((int) *src++ + 1.7790 * ((int) *u - 128));*/
			*dstbuf++ = citb((int) *src + 1.140 * ((int) *v - 128));
			*dstbuf++ = citb((int) *src - 0.396 * ((int) *u - 128) - 0.581 * ((int) *v - 128));
			*dstbuf++ = citb((int) *src++ + 2.029 * ((int) *u - 128));
			
			uvc++;
			if (uvc >= 2)
			{
				uvc = 0;
				u++;
				v++;
			}
		}

		buvc++;
		if (buvc < 2)
		{
			u = bu;
			v = bv;
		}
		else
			buvc = 0;
	}
}

static
void
unpalette_rgb24(struct image *dst, unsigned char *src)
{
	memcpy(dst->buf, src, dst->bufsize);
}

static
void
unpalette_bgr24(struct image *dst, unsigned char *src)
{
	unsigned char *dstbuf, *dstend;
	
	dstbuf = dst->buf;
	dstend = dstbuf + dst->bufsize; 
	while (dstbuf < dstend)
	{
		dstbuf[0] = src[2];
		dstbuf[1] = src[1];
		dstbuf[2] = src[0];
		dstbuf += 3;
		src += 3;
	}
}

static
void
unpalette_rgb32(struct image *dst, unsigned char *src)
{
	unsigned char *dstbuf, *dstend;
	
	dstbuf = dst->buf;
	dstend = dstbuf + dst->bufsize; 
	while (dstbuf < dstend)
	{
		*dstbuf++ = *src++;
		*dstbuf++ = *src++;
		*dstbuf++ = *src++;
		src++;
	}
}

static
void
unpalette_bgr32(struct image *dst, unsigned char *src)
{
	unsigned char *dstbuf, *dstend;
	
	dstbuf = dst->buf;
	dstend = dstbuf + dst->bufsize; 
	while (dstbuf < dstend)
	{
		dstbuf[0] = src[2];
		dstbuf[1] = src[1];
		dstbuf[2] = src[0];
		dstbuf += 3;
		src += 4;
	}
}

static
void
unpalette_grey(struct image *dst, unsigned char *src)
{
	unsigned char *dstbuf, *dstend;
	
	dstbuf = dst->buf;
	dstend = dstbuf + dst->bufsize; 
	while (dstbuf < dstend)
	{
		*dstbuf++ = *src;
		*dstbuf++ = *src;
		*dstbuf++ = *src++;
	}
}

static
void
unpalette_yuyv(struct image *dst, unsigned char *src)
{
	unsigned char *dbuf, *dend;
	unsigned char u, v;
	int i;
	
	dbuf = dst->buf;
	dend = dbuf + dst->bufsize;
	
	while (dbuf < dend)
	{
		u = src[1];
		v = src[3];

		for (i = 0; i < 2; i++)
		{
			*dbuf++ = citb((int) *src + 1.140 * ((int) v - 128));
			*dbuf++ = citb((int) *src - 0.396 * ((int) u - 128) - 0.581 * ((int) v - 128));
			*dbuf++ = citb((int) *src + 2.029 * ((int) u - 128));
			src += 2;
		}
	}
}

static
void
unpalette_yuv420(struct image *dst, unsigned char *src)
{
	unsigned char *dbuf, *dend;
	unsigned char *u, *v;
	int ypl, bpl;
	int i, j, k, l;

	dbuf = dst->buf;
	dend = dbuf + dst->bufsize;
	
	u = src + 4;
	bpl = dst->width * 1.5;
	v = u + bpl;
	ypl = dst->width / 4;
	
	/* YYYY UU YYYY UU
	 * YYYY VV YYYY VV */
	while (dbuf < dend)
	{
		for (l = 0; l < 2; l++)
		{
			for (k = 0; k < ypl; k++)
			{
				for (j = 0; j < 2; j++)
				{
					for (i = 0; i < 2; i++)
					{
						*dbuf++ = citb((int) *src + 1.140 * ((int) *v - 128));
						*dbuf++ = citb((int) *src - 0.396 * ((int) *u - 128) - 0.581 * ((int) *v - 128));
						*dbuf++ = citb((int) *src + 2.029 * ((int) *u - 128));
						src++;
					}
					u++;
					v++;
				}
				src += 2;
				u += 4;
				v += 4;
			}
			u -= bpl;
			v -= bpl;
		}
		u += bpl * 2;
		v += bpl * 2;
	}
}

static
void
unpalette_rgb565(struct image *dst, unsigned char *src)
{
	unsigned char *dbuf, *dend;

	dbuf = dst->buf;
	dend = dbuf + dst->bufsize;

	while (dbuf < dend)
	{
		/* rrrrrggg gggbbbbb -> gggbbbbb rrrrrggg */
		*dbuf++ = (src[1] & 0xf8) | ((src[1] >> 3) & 0x07);
		*dbuf++ = (src[1] << 5) | ((src[0] >> 3) & 0x1c) | ((src[0] >> 5) & 0x03);
		*dbuf++ = (src[0] << 3) | (src[0] & 0x07);
		src += 2;
	}
}

static
void
unpalette_rgb555(struct image *dst, unsigned char *src)
{
	unsigned char *dbuf, *dend;

	dbuf = dst->buf;
	dend = dbuf + dst->bufsize;

	while (dbuf < dend)
	{
		/* 0rrrrrgg gggbbbbb -> gggbbbbb 0rrrrrgg */
		*dbuf++ = ((src[1] << 1) & 0xf8) | ((src[1] >> 2) & 0x07);
		*dbuf++ = (src[1] << 6) | ((src[0] >> 2) & 0x38) | ((src[0] >> 5) & 0x07);
		*dbuf++ = (src[0] << 3) | (src[0] & 0x07);
		src += 2;
	}
}


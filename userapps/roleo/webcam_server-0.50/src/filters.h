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

#ifndef _FILTERS_H_INCLUDED_
#define _FILTERS_H_INCLUDED_

void rotate_image(struct image* img, int rot);
int compare_images(unsigned char *last, unsigned char *current, int width, int height);
void fliph(struct image* img);
void flipv(struct image* img);
void swap_rgb24(struct image* img);
void adjust_gamma(struct image* img, int corr);
void add_text(struct image* img, char *text, struct RGB fg, struct RGB bg, struct RGB trans, int xpos, int ypos);
int image2jpeg(struct image* img, char **jpeg_data, int quality);

#endif

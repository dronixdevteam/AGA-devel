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

#ifndef _CAMERA_H_INCLUDED_
#define _CAMERA_H_INCLUDED_

int open_cam(struct caminfo *cam, char *devfile);
int close_cam(struct caminfo *cam);
int set_cam_info(struct caminfo *cam);
void get_cam_info(struct caminfo *cam);
struct image *get_cam_image(struct caminfo *cam);

#endif

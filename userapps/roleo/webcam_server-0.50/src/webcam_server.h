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

#ifndef _WEBCAM_SERVER_H_INCLUDED_
#define _WEBCAM_SERVER_H_INCLUDED_

#include "unpalette.h"
#include "image.h"

void print_rgb(char * hdr, struct RGB x);
char *str_replace(const char *str, const char *find, const char *replace);

struct options
{
	int port;
	int verbose;
	int daemon;
	int retry_init;
	char *caption;
	char *devfile;
	int jpeg_quality;
	int width;
	int height;
	int swap_rgb;
	int test_fps;
	int flip_horiz;
	int flip_vert;
	int rotate;
	int gamma;
	struct RGB text_fg;
	struct RGB text_bg;
	struct RGB trans;
	int text_xpos;
	int text_ypos;
	int use_read;
	int palette;
	
	int allow_http;
	int allow_stream;
	
	int max_stream_bytes;
	int max_stream_seconds;
	int max_stream_frames;
	
/* ** currently not implemented
	int allow_admin;
	char *admin_pw;
*/
	char *logfile;
};

struct status
{
	int num_users;
	int id_newest_img;
	int bad_grabs;
};

struct caminfo
{
	int dev;
	FILE *log;
	int grab_thread_alive;
	pthread_t pt_grab;

	pthread_mutex_t lock_id;
	pthread_mutex_t lock_info;
	pthread_mutex_t lock_queue;
	pthread_mutex_t lock_log;
	sem_t sem_con;

	struct options o;
	struct status s;
	struct imagequeue *queue;

	struct palette *pal;

	struct video_capability vid_caps;
	struct video_window vid_win;
	struct video_picture vid_pic;
	struct video_mbuf vid_mbuf;
	struct video_mmap vid_v4lmmap;
	unsigned char *mmap;
};

void usage();
int parse_args(struct caminfo *cam, int argc, char *argv[]);
void log(struct caminfo *cam, char *text);
int create_and_listen(int port);

#endif

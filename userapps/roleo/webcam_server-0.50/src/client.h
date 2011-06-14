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

#ifndef _CLIENT_H_INCLUDED_
#define _CLIENT_H_INCLUDED_

struct connection
{
	int socketfd;
	struct sockaddr_in remote_addr;
	u_long total_bytes;
	u_long total_frames;
	u_long id_last;
	int old_images;
	int client_type;
	
	struct caminfo *cam;
	
	time_t start;
	time_t end;
};

int handle_connection(struct connection *con);
int check_limits(struct caminfo *cam, struct connection *con);
int get_client_type(struct caminfo *cam, char *buffer);
int match_client_type(char *data, char *tag, char *version);
/* ** currently not implemented
int match_admin_password(char *buffer, char *password);
int handle_admin_connection(struct caminfo *cam, struct connection *con, char *request);
*/

#endif

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

#include "version.h"

char *get_version()
{
	static char *version = NULL;
	
	if(version == NULL)
	{
		version = (char*)malloc(64);
		sprintf(version, "%d.%d", MAJOR, MINOR);
	}
	
	return version;
}

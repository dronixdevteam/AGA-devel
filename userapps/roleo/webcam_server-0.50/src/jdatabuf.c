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

#ifndef _WCSJPEG_H_INCLUDED_
#define _WCSJPEG_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "jdatabuf.h"

#define DEFAULT_JPEG_SIZE	20000	/* default jpeg size (bytes) */

/*-----------------------------------------------------------
  jpeg data buffer stuff
  -----------------------------------------------------------*/

//METHODDEF(void)
void
init_destination (j_compress_ptr cinfo)
{
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

  dest->buffer = (char *)malloc(DEFAULT_JPEG_SIZE * sizeof(JOCTET));
  
  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = DEFAULT_JPEG_SIZE;
  dest->total_buffer_size = DEFAULT_JPEG_SIZE;
}

//METHODDEF(boolean)
boolean
empty_output_buffer (j_compress_ptr cinfo)
{
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
  u_char *tmp;
  long size;

  size = dest->total_buffer_size;

  /* re-allocate more memory (another DEFAULT_JPEG_SIZE block) */
  tmp = (char *)realloc(dest->buffer, (dest->total_buffer_size + DEFAULT_JPEG_SIZE) * sizeof(JOCTET));
  if(tmp == NULL)
  {
    fprintf(stderr, "empty_output_buffer: couldn't allocate more memory for jpeg (%ld bytes)\n",
            (dest->total_buffer_size + DEFAULT_JPEG_SIZE) * sizeof(JOCTET));
    return FALSE;
  }
  dest->total_buffer_size += DEFAULT_JPEG_SIZE;
  dest->buffer = tmp;
  /* reset the free_in_buffer counter */
  dest->pub.free_in_buffer = dest->total_buffer_size - size;
  dest->pub.next_output_byte = dest->buffer + size;
  return TRUE;
}

//METHODDEF(void)
void
term_destination (j_compress_ptr cinfo)
{
}

//GLOBAL(void)
void
jpeg_buff_dest (j_compress_ptr cinfo)
{
  my_dest_ptr dest;

  if (cinfo->dest == NULL) {	/* first time for this JPEG object? */
    cinfo->dest = (struct jpeg_destination_mgr *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				  sizeof(my_destination_mgr));
  }

  dest = (my_dest_ptr) cinfo->dest;
  dest->pub.init_destination = init_destination;
  dest->pub.empty_output_buffer = empty_output_buffer;
  dest->pub.term_destination = term_destination;
}

//METHODDEF(long)
long
get_jpeg_size (j_compress_ptr cinfo)
{
	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
	
	return (long)(dest->pub.next_output_byte - dest->buffer);
}

//METHODDEF(void)
void
jpeg_buff_free (j_compress_ptr cinfo)
{
  my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
  
  free(dest->buffer);
}

#endif

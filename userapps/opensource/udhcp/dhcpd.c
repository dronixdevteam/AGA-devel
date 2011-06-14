/* dhcpd.c
 *
 * Moreton Bay DHCP Server
 * Copyright (C) 1999 Matthew Ramsay <matthewr@moreton.com.au>
 *			Chris Trew <ctrew@moreton.com.au>
 *
 * Rewrite by Russ Dill <Russ.Dill@asu.edu> July 2001
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>

#include "debug.h"
#include "dhcpd.h"
#include "arpping.h"
#include "socket.h"
#include "options.h"
#include "files.h"
#include "leases.h"
#include "packet.h"
#include "serverpacket.h"
#include "pidfile.h"
#include "static_leases.h"


/* globals */
struct dhcpOfferedAddr *leases;
struct server_config_t server_config;
// BRCM_begin
struct dhcpOfferedAddr *declines;
struct vendor_id_config_t vendor_id_config[MAX_VENDOR_IDS];

static int vendor_id_cfg = 0;
// BRCM_end

/* Exit and cleanup */
static void exit_server(int retval)
{
	pidfile_delete(server_config.pidfile);
	CLOSE_LOG();
	exit(retval);
}


/* SIGTERM handler */
static void udhcpd_killed(int sig)
{
	sig = 0;
	LOG(LOG_INFO, "Received SIGTERM");
	exit_server(0);
}


#ifdef COMBINED_BINARY	
int udhcpd(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{	
	fd_set rfds;
	struct timeval tv;
        //BRCM --initialize server_socket to -1
	int server_socket = -1;
	int bytes, retval;
	struct dhcpMessage packet;
	unsigned char *state;
        // BRCM added vendorid
	char *server_id, *requested, *hostname, *vendorid = NULL;
	u_int32_t server_id_align, requested_align;
	unsigned long timeout_end;
	struct option_set *option;
	struct dhcpOfferedAddr *lease;
	struct dhcpOfferedAddr static_lease;
	struct sockaddr_in *sin;
	int pid_fd;
	uint32_t static_lease_ip;
			
	/* server ip addr */
	int fd = -1;
	struct ifreq ifr;
	// BRCM_begin
        int i = 0;
        char opt_vend[64];
        // BRCM_end

	argc = argv[0][0]; /* get rid of some warnings */
	
	OPEN_LOG("udhcpd");
	LOG(LOG_INFO, "udhcp server (v%s) started", VERSION);
	
	pid_fd = pidfile_acquire(server_config.pidfile);
	pidfile_write_release(pid_fd);

	memset(&server_config, 0, sizeof(struct server_config_t));
	
	read_config(DHCPD_CONF_FILE);
	read_config_static_leases(DHCPD_STATIC_LEASES_FILE);
	if ((option = find_option(server_config.options, DHCP_LEASE_TIME))) {
		memcpy(&server_config.lease, option->data + 2, 4);
		server_config.lease = ntohl(server_config.lease);
	}
	else server_config.lease = LEASE_TIME;
	
	leases = malloc(sizeof(struct dhcpOfferedAddr) * server_config.max_leases);
	memset(leases, 0, sizeof(struct dhcpOfferedAddr) * server_config.max_leases);
	read_leases(server_config.lease_file);

        // BRCM
	declines = malloc(sizeof(struct dhcpOfferedAddr));

	if((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) >= 0) {
		ifr.ifr_addr.sa_family = AF_INET;
		strcpy(ifr.ifr_name, server_config.interface);
		if (ioctl(fd, SIOCGIFADDR, &ifr) == 0) {
			sin = (struct sockaddr_in *) &ifr.ifr_addr;
			server_config.server = sin->sin_addr.s_addr;
			DEBUG(LOG_INFO, "%s (server_ip) = %s", ifr.ifr_name, inet_ntoa(sin->sin_addr));
		} else {
			LOG(LOG_ERR, "SIOCGIFADDR failed!");
			exit_server(1);
		}
		if (ioctl(fd, SIOCGIFINDEX, &ifr) == 0) {
			DEBUG(LOG_INFO, "adapter index %d", ifr.ifr_ifindex);
			server_config.ifindex = ifr.ifr_ifindex;
		} else {
			LOG(LOG_ERR, "SIOCGIFINDEX failed!");
			exit_server(1);
		}
		if (ioctl(fd, SIOCGIFHWADDR, &ifr) == 0) {
			memcpy(server_config.arp, ifr.ifr_hwaddr.sa_data, 6);
			DEBUG(LOG_INFO, "adapter hardware address %02x:%02x:%02x:%02x:%02x:%02x",
				server_config.arp[0], server_config.arp[1], server_config.arp[2], 
				server_config.arp[3], server_config.arp[4], server_config.arp[5]);
		} else {
			LOG(LOG_ERR, "SIOCGIFHWADDR failed!");
			exit_server(1);
		}
	} else {
		LOG(LOG_ERR, "socket failed!");
		exit_server(1);
	}
	close(fd);

#ifndef DEBUGGING
	pid_fd = pidfile_acquire(server_config.pidfile); /* hold lock during fork. */
	switch(fork()) {
	case -1:
		perror("fork");
		exit_server(1);
		/*NOTREACHED*/
	case 0:
		break; /* child continues */
	default:
		exit(0); /* parent exits */
		/*NOTREACHED*/
		}
	close(0);
	setsid();
	pidfile_write_release(pid_fd);
#endif


	signal(SIGUSR1, write_leases);
	signal(SIGTERM, udhcpd_killed);

	timeout_end = time(0) + server_config.auto_time;

	while(1) { /* loop until universe collapses */
                //BRCM_begin
                int declined = 0;
                if (server_socket < 0) {
                     server_socket = listen_socket(INADDR_ANY, SERVER_PORT, server_config.interface);
                     if(server_socket < 0) {
                           LOG(LOG_ERR, "couldn't create server socket -- au revoir");
                           exit_server(0);
                     }			
                }  //BRCM_end

		FD_ZERO(&rfds);
		FD_SET(server_socket, &rfds);
		if (server_config.auto_time) {
			tv.tv_sec = timeout_end - time(0);
			if (tv.tv_sec <= 0) {
				tv.tv_sec = server_config.auto_time;
				timeout_end = time(0) + server_config.auto_time;
				write_leases(0);
			}
			tv.tv_usec = 0;
		}
		retval = select(server_socket + 1, &rfds, NULL, NULL, server_config.auto_time ? &tv : NULL);
		if (retval == 0) {
			write_leases(0);
			timeout_end = time(0) + server_config.auto_time;
                        close(server_socket);
                        //BRCM
                        server_socket = -1;
			continue;
		} else if (retval < 0) {
			DEBUG(LOG_INFO, "error on select");
			close(server_socket);
                        //BRCM
                        server_socket = -1;
			continue;
		}
		
		bytes = get_packet(&packet, server_socket); /* this waits for a packet - idle */
                //BRCM_BEGIN
                //close(server_socket);
		if(bytes < 0)
			continue;

		if((state = get_option(&packet, DHCP_MESSAGE_TYPE)) == NULL) {
			DEBUG(LOG_ERR, "couldnt get option from packet -- ignoring");
			continue;
		}

		/* Look for a static lease */
		static_lease_ip = getIpByMac(server_config.static_leases, &packet.chaddr);

		if(static_lease_ip)
		{
			LOG(LOG_INFO, "Found static lease: %x\n", static_lease_ip);

			memcpy(&static_lease.chaddr, &packet.chaddr, 16);
			static_lease.yiaddr = static_lease_ip;
			static_lease.expires = 0;

			lease = &static_lease;

		}
		else
		{
			lease = find_lease_by_chaddr(packet.chaddr);
		}
		
		switch (state[0]) {
		case DHCPDISCOVER:
			DEBUG(LOG_INFO,"received DISCOVER");
			//BRCM_begin
                        vendorid = get_option(&packet, DHCP_VENDOR);

                        /* Check the vendor ID with the configured vendor ID */
                        if (read_vendor_id_config(DHCPD_VENDORID_CONF_FILE) == 1) {
                                vendor_id_cfg = 1;
                        }
                        if (vendor_id_cfg) {
                                int i = 0;
                                for (i = 0; i < MAX_VENDOR_IDS; i++) {
                                        if (strlen(vendor_id_config[i].vendorid) == 0) {
                                                continue;
                                        }
                                        memset(opt_vend, 0, 64);
                                        memcpy(opt_vend, vendorid, strlen(vendor_id_config[i].vendorid) - 1);
                                        if (strncmp(opt_vend, vendor_id_config[i].vendorid,
                                                strlen(vendor_id_config[i].vendorid) - 1) == 0) {
                                                memset(declines, 0, sizeof(struct dhcpOfferedAddr));
                                                memcpy(declines->chaddr, packet.chaddr, 16);
                                                memcpy(declines->vendorid, vendorid, 64);
                                                /* Write this to the decline file */
                                                write_decline(0);
                                                /* remain silent */
                                                sendNAK(&packet);
                                                declined = 1;
                                                break;
                                        }
                                }
                        }
			// BRCM_end

                        if (!declined) {
				if (sendOffer(&packet) < 0) {
					LOG(LOG_ERR, "send OFFER failed -- ignoring");
				}
			}
			break;			
 		case DHCPREQUEST:
			DEBUG(LOG_INFO,"received REQUEST");

			requested = get_option(&packet, DHCP_REQUESTED_IP);
			server_id = get_option(&packet, DHCP_SERVER_ID);
			hostname = get_option(&packet, DHCP_HOST_NAME);
			if (requested) memcpy(&requested_align, requested, 4);
			if (server_id) memcpy(&server_id_align, server_id, 4);
		
			if (lease) {
				if (server_id) {
					/* SELECTING State */
					DEBUG(LOG_INFO, "server_id = %08x", ntohl(server_id_align));
					if (server_id_align == server_config.server && requested && 
					    requested_align == lease->yiaddr) {
						sendACK(&packet, lease->yiaddr);
					}
				} else {
					if (requested) {
						/* INIT-REBOOT State */
						if (lease->yiaddr == requested_align)
							sendACK(&packet, lease->yiaddr);
						else sendNAK(&packet);
					} else {
						/* RENEWING or REBINDING State */
						if (lease->yiaddr == packet.ciaddr)
							sendACK(&packet, lease->yiaddr);
						else {
							/* don't know what to do!!!! */
							sendNAK(&packet);
						}
					}						
				}
				if (hostname) {
					bytes = hostname[-1];
					if (bytes >= (int) sizeof(lease->hostname))
						bytes = sizeof(lease->hostname) - 1;
					strncpy(lease->hostname, hostname, bytes);
					lease->hostname[bytes] = '\0';
				} else
					lease->hostname[0] = '\0';
			} else { /* else remain silent */				
    			    sendNAK(&packet);
        		}
			break;
		case DHCPDECLINE:
			DEBUG(LOG_INFO,"received DECLINE");
			if (lease) {
				memset(lease->chaddr, 0, 16);
				lease->expires = time(0) + server_config.decline_time;
			}			
			break;
		case DHCPRELEASE:
			DEBUG(LOG_INFO,"received RELEASE");
			if (lease) lease->expires = time(0);
			break;
		case DHCPINFORM:
			DEBUG(LOG_INFO,"received INFORM");
			send_inform(&packet);
			break;	
		default:
			LOG(LOG_WARNING, "unsupported DHCP message (%02x) -- ignoring", state[0]);
		}
	}
        //BRCM_BEGIN 
        if (server_socket > 0)
          close(server_socket);
	return 0;
}


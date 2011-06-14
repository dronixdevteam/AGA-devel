#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "wol.h"

int hextobin(unsigned char c)
{
/*
    Function to convert hex character to binary.
    Returns value or -1 if there is any error.
*/
    if(isdigit(c))		return c-'0';
    else if(isxdigit(c))	return tolower(c)-'a'+10;
    else			return -1;
}

void print_usage(char *name)
{
    printf("Usage: %s if_name mac_address\n", name);
    printf("\t\tif_name:       network interface name to use\n");
    printf("\t\tmac_address:   mac address of the destination device\n");
}

int main(int argc, char *argv[])
{
    char macAddress[18];
    char ifName[64];
    const int on = 1;
    short int cont;
    int skt_target;
    unsigned char ma[6];
    unsigned char packet[102];

    char buff[1024];
    struct sockaddr_in sindst;
    struct ifreq *ifr = NULL;
    struct ifconf ifc;
    int i, if_found = 0;
    int iRet = 0;
    
    if (argc != 3) {
	print_usage(argv[0]);
	exit(-1);
    }
    
    snprintf(ifName, 64, argv[1]);
    snprintf(macAddress, 18, argv[2]);
    
    // Test length of argument
    if (strlen(macAddress) != 17)
    {
    	fprintf(stderr, "Mac address incorrect: use 12:34:56:78:90:ab or any other separator\n");
	exit(-2);
    }
	
    // Test and convert hex string to binary
    ma[0]=0;
    ma[1]=0;
    ma[2]=0;
    ma[3]=0;
    ma[4]=0;
    ma[5]=0;

    for (cont=0;cont<18;cont++)
    {
	if (cont%3 != 2)
	{
	    if ((macAddress[cont] < '0' || macAddress[cont] > '9') &&
		(macAddress[cont] < 'A' || macAddress[cont] > 'F') &&
		(macAddress[cont] < 'a' || macAddress[cont] > 'f'))
	    {
    		fprintf(stderr, "Mac address incorrect: use 12:34:56:78:90:ab or any other separator\n");
		exit(-3);
    	    }
	    else
	    {
		ma[cont/3]=ma[cont/3]*16+hextobin(macAddress[cont]);
	    }
	}
    }    

    // Create broadcast magic packet
    // 6*FF + 16*MAC_ADDRESS
    for(cont=0;cont<=5;cont++)
        packet[cont]='\xFF';

    for(cont=0;cont<=15;cont++)
    {
        packet[6+cont*6] = ma[0];
        packet[7+cont*6] = ma[1];
	packet[8+cont*6] = ma[2];
	packet[9+cont*6] = ma[3];
	packet[10+cont*6] = ma[4];
	packet[11+cont*6] = ma[5];
    }

    // Open Socket
    skt_target = socket( AF_INET, SOCK_DGRAM, 0);
    if (  skt_target < 0 ) {
        fprintf( stderr, "Cannot open SOCKET.\n");
        exit(-4);
    }

    // Prepare dest address
    memset (&sindst,0,sizeof (sindst));
    sindst.sin_family = AF_INET;
    sindst.sin_port = htons (PORT);

    // Retrieve interfaces informations
    ifc.ifc_len = sizeof(buff);
    ifc.ifc_buf = buff;

    if (ioctl(skt_target, SIOCGIFCONF, &ifc) < 0) {
	perror("ioctl SIOCGIFCONF");
	return(-5);
    }

    ifr = ifc.ifc_req;
    
    // Retrieve the interface broadcast address
    for (i = ifc.ifc_len / sizeof(struct ifreq); --i >= 0; ifr++) 
    {
	if (strncmp(ifName, ifr->ifr_name, 3) == 0) {
    	    if_found = 1;

	    if (ioctl(skt_target, SIOCGIFBRDADDR, ifr) < 0) {
		perror("ioctl SIOCGIFBRDADDR");
		return(-6);
	    }

//	    printf("  Broadcast: %s\n", inet_ntoa(((struct sockaddr_in *) 
//		&(ifr->ifr_broadaddr))->sin_addr));
	    
	    sindst.sin_addr = ((struct sockaddr_in *) 
		&(ifr->ifr_broadaddr))->sin_addr;
	    break;
	}
    }

    if (if_found == 0) {
	return(-7);
    }
	
    // Set up Broadcast
    iRet = setsockopt (skt_target, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
    if (iRet != 0) {
	return(-8);
    }

    // Send UDP packet
    iRet = (int) sendto( skt_target, packet, 102, 0,
        (struct sockaddr*)&sindst, sizeof(sindst));
    if (iRet != 102) {
	return(-9);
    }

    // Close socket and exit
    close (skt_target);
    printf("Packet sent successfully\n");
    
    return 0;
}

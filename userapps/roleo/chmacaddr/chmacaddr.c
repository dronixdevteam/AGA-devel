#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "board_api.h"
#include "chmacaddr.h"
#include "bcm_puzzle.h"

void usage(char *strname)
{
    printf("Usage:\n");
    printf("%s --showonly\n", strname);
    printf("\t\tto show current base mac address\n");
    printf("%s xx:xx:xx:xx:xx:xx\n", strname);
    printf("\t\tto change current base mac address\n");
}

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

int main(int argc, char *argv[])
{
    NVRAM_DATA nvramData;
    UINT32 crc = CRC32_INIT_VALUE;
    unsigned char ma[NVRAM_MAC_ADDRESS_LEN];
    int cont, iRet = 0;
    
    if (argc == 2) {
	if (strcasecmp(argv[1], "--showonly") == 0) {
	    sysNvRamGet((char *) &nvramData, sizeof(nvramData), 0);

	    for (cont=0; cont<5; cont++) {
		printf("%02x",nvramData.ucaBaseMacAddr[cont]);
		printf(":");
	    }
	    printf("%02x\n", nvramData.ucaBaseMacAddr[5]);
	} else {
	    // Test address length
	    if (strlen(argv[1]) != 17) {
		usage(argv[0]);
		iRet = -2;
	    }

	    // Test and convert hex string to unsigned char
	    ma[0]=0;
	    ma[1]=0;
	    ma[2]=0;
	    ma[3]=0;
	    ma[4]=0;
	    ma[5]=0;

	    for (cont=0;cont<18;cont++) {
		if (cont%3 != 2) {
		    if ((argv[1][cont] < '0' || argv[1][cont] > '9') &&
			(argv[1][cont] < 'A' || argv[1][cont] > 'F') &&
			(argv[1][cont] < 'a' || argv[1][cont] > 'f')) {
    		
			usage(argv[0]);
			iRet = -3;
    		    } else {
			ma[cont/3]=ma[cont/3]*16+hextobin(argv[1][cont]);
		    }
		}
	    }

	    //printf("%02x:%02x:%02x:%02x:%02x:%02x\n", ma[0], ma[1], ma[2], ma[3], ma[4], ma[5]);
	    sysNvRamGet((char *) &nvramData, sizeof(nvramData), 0);
	    
	    memcpy(&nvramData.ucaBaseMacAddr[0], ma, NVRAM_MAC_ADDRESS_LEN);
	    nvramData.ulCheckSum = 0;
	    crc = getCrc32((char *)&nvramData, (UINT32) sizeof(NVRAM_DATA), crc);
	    nvramData.ulCheckSum = crc;
    
	    //printf("%ld\n", crc);
	    sysNvRamSet((char *) &nvramData, sizeof(nvramData), 0);

	    printf("MAC address has been updated.\n");
	    printf("Restart the system to make changes effective.\n");

	}
    } else {
	usage(argv[0]);
	iRet = -1;
    }

    return iRet;
}

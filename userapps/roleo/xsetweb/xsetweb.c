#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <psixml.h>
#include "nanoxml.h"
#include "xsetweb.h"
#include "../shared/psi_api.h"
#include "../shared/util.h"

void usage(char *strname)
{
    printf("Usage: %s enable/disable\n", strname);
    printf("\nbefore running this program, you need to configure http access to enable Extra Settings web pages\n");
}
	    
int main(int argc, char*argv[])
{
    int iRet = 0;
    int iResult = 0;
    int accessGranted;
    char sCommand[256];
    
    if (argc != 2) {
	usage(argv[0]);
	return -1;
    }

    accessGranted = verifyWANAccess(81);
    
    if (strcmp("enable", argv[1])==0) {
	if (accessGranted == 0) {
	    iResult = configure_xsetweb();
	    if (iResult == 0) {
		printf("Extra Settings web pages enabled\n");
	    } else if (iResult == -1) {
		printf("http access is disabled, enable it before running this command\n");
		iRet = -1;
	    } else {
		printf("Error configuring Extra Settings web pages\n");
		iRet = -2;
	    }
	} else {
	    printf("Extra Settings web pages are already enabled\n");
	}    
    } else if (strcmp("disable", argv[1])==0) {
	if (accessGranted == 1) {
	    sprintf(sCommand, "%s -D INPUT %s", IPTABLES, COMMON_PARMS);
	    system(sCommand);
	    printf("Extra Settings web pages disabled\n");
	} else {
	    printf("Extra Settings web pages are already disabled\n");
	}
    } else {
	usage(argv[0]);
	iRet = -3;
    }
    
    return iRet;
}

int configure_xsetweb()
{
    int iRet = 0;
    char sCommand[256];
    
    // Reading Access Control parameters
    strcpy(str_tag1_name, "SecCfg");
    strcpy(str_tag2_name, "srvCtrlList");
    strcpy(str_attribute_name, "http");
    read_attribute();
    if (find_status.value_found == 1) {
	if ((strcasecmp("wan", str_attribute_value) == 0) ||
	    (strcasecmp("enable", str_attribute_value) == 0)) {
		
	    sprintf(sCommand, "%s -I INPUT %s", IPTABLES, COMMON_PARMS);
	    system(sCommand);
	} else {
	    iRet = -1;
	}
    } else {
	iRet = -2;
    }
    return iRet;
}

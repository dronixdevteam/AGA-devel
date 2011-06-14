#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../shared/rsi_api.h"
#include "../shared/util.h"
#include "regbutton.h"

void usage(char *strname)
{
    printf("Usage: %s command\n", strname);
}
	    
int main(int argc, char*argv[])
{
    int iRet = 0;

    char strAction[256];
    
    strAction[0] = '\0';
    
    // Reading regbutton configuration
    strcpy(str_tag1_name, "regbutton");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "action");
    read_attribute();
    if (find_status.value_found == 1) {
        sprintf(strAction, "%s", str_attribute_value);
    } else {
	iRet = -1;
    }
    
    if (strcasecmp("none", strAction) == 0) {
	return 0;
    } else if (strcasecmp("wradio", strAction) == 0) {
	iRet = rb_wradio();
    } else if (strcasecmp("reboot", strAction) == 0) {
	iRet = system("/sbin/reboot");
    } else if (strcasecmp("resync", strAction) == 0) {
	iRet = system("/bin/rsiconf adslctl --force");
    } else if (strcasecmp("umount", strAction) == 0) {
	iRet = rb_umount();
    } else if (strcasecmp("stealth", strAction) == 0) {
	iRet += system("/sbin/ifconfig wl0 down");
	iRet += system("/bin/wlctl radio off");
	iRet += rb_stealth();
    } else if (strcasecmp("script", strAction) == 0) {
	iRet = rb_script();
    } else {
	printf("Unknown command\n");
	iRet = -2;
    }

    sleep(1);
    if (iRet == 0) {
	system("/bin/ledctrl VoipGreen On");
    } else {
	system("/bin/ledctrl VoipRed On");
    }
    sleep(1);
    system("/bin/ledctrl VoipGreen Off");
    system("/bin/ledctrl VoipRed Off");
    
    return iRet;
}

int rb_wradio()
{
    FILE *fp;
    char line[256];
    int iRet = 0;

    fp = popen("/bin/wlctl radio", "r");
    if (fp != NULL) {
        fgets(line, sizeof(line), fp);
        pclose(fp);
        if (strncasecmp("radio is on", line, 11) == 0) {
	    iRet += system("/sbin/ifconfig wl0 down");
	    iRet += system("/bin/wlctl radio off");
	} else if (strncasecmp("radio is off", line, 12) == 0) {
	    iRet += system("/bin/wlctl radio on");
	    iRet += system("/sbin/ifconfig wl0 up");
	}
    } else {
	iRet = -1;
    }
    
    return iRet;
}

int rb_umount()
{
    int iRet=0;
    FILE *fs;
    char sMDev[64], sMPoint[64];
    char s1[64], s2[64], s3[64], s4[64];
    char strCommand[256];
    
    strCommand[0] = '\0';

    if ((fs=fopen("/proc/mounts","r")) != NULL) {
        while (fscanf(fs, "%s%s%s%s%s%s", sMDev, sMPoint, s1, s2, s3, s4) != EOF) {
	    //printf ("%s %s\n", sMDev, sMPoint);
	    if (strncmp(sMPoint, "/var/mounts", 11) == 0) {
		sprintf(strCommand, "/bin/kill `/bin/lsof -t %s`", sMPoint);
		iRet += system(strCommand);
		sleep(1);
		sprintf(strCommand, "/bin/umount %s", sMDev);
		iRet += system(strCommand);
	    }
	}
	fclose(fs);
    } else {
	iRet = -1;
    }
    	 
    return iRet;
}

int rb_stealth()
{
    system("/bin/ledctrl Adsl Off");
    system("/bin/ledctrl PPP Off");
    system("/bin/ledctrl Wireless Off");
    system("/bin/ledctrl Usb Off");
    system("/bin/ledctrl Power Off");

    return 0;
}

int rb_script()
{
    int iRet = 0;
    char strScript[5120];
    FILE *fs;
        
    // Reading regbutton parms
    strcpy(str_tag1_name, "regbutton");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "script");
    read_attribute_big();
    if (find_status.value_found == 1) {
        sprintf(strScript, "%s", str_attribute_value_big);
    }
    unescape_url(strScript);

    if ((fs=fopen("/var/regbutton", "wb")) != NULL) {
        fwrite(strScript, 1, strlen(strScript), fs);
        fclose(fs);
	iRet = system("/bin/sh /var/regbutton");
    } else {
        iRet = -1;
    }

    return iRet;
}

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <psixml.h>
#include "nanoxml.h"
#include "errno.h"

#include "webcam.h"
#include "../../shared/rsi_api.h"

int GetWebcamConf()
{
    int iRet=0;
    int iState = 0;
    char strModulePath[256];
    int iWAN = 0;
    char strCaption[256];
    int iWidth = -1;
    int iHeight = -1;
    int iFps = -1;
    int iQuality = -1;
    int iTcpport = -1;
    char strTmp[256];
    char strCommand[256];
    char strDriverName[256];
    int iTmp = -1;
    
    strcpy(strModulePath, "spca5xx");
    strcpy(strCaption, "default");
    strTmp[0]='\0';
    strCommand[0]='\0';
    
    // Reading webcam parms
    strcpy(str_tag1_name, "webcam");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
        sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
            iState = 1;
        } else {
            iState = 0;
        }

        strcpy(str_attribute_name, "modulepath");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strModulePath, "%s", str_attribute_value);
        }

        strcpy(str_attribute_name, "wan");
        read_attribute();
        if (find_status.value_found == 1) {
    	    sprintf(strTmp, "%s", str_attribute_value);
    	    if (strcasecmp("enable", strTmp) == 0) {
        	iWAN = 1;
    	    } else {
        	iWAN = 0;
    	    }
        }

        strcpy(str_attribute_name, "caption");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strCaption, "%s", str_attribute_value);
        }

        strcpy(str_attribute_name, "width");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iWidth = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -1;
            }
        }

        strcpy(str_attribute_name, "height");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iHeight = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -2;
            }
        }

        strcpy(str_attribute_name, "fps");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iFps = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -3;
            }
        }

        strcpy(str_attribute_name, "quality");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iQuality = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -4;
            }
        }

        strcpy(str_attribute_name, "tcpport");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iTcpport = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -5;
            }
        }
    } else {
        iRet = -6;
    }

    if (iState == 0) {
	printf("var ena = false;\n");
    } else {
	printf("var ena = true;\n");
    }
    unescape_url(strModulePath);
    if (strcasecmp(strModulePath, "spca5xx") == 0) {
	printf("var strmodulepath = '';\n");
    } else {
	printf("var strmodulepath = '%s';\n", strModulePath);
    }
    if (iWAN == 0) {
	printf("var wan = false;\n");
    } else {
	printf("var wan = true;\n");
    }
    unescape_url(strCaption);
    if (strcasecmp(strCaption, "default") == 0) {
	printf("var strcaption = '';\n");
    } else {
	printf("var strcaption = '%s';\n", strCaption);
    }
    if (iWidth == -1) {
	printf("var iwidth = '';\n");
    } else {
	printf("var iwidth = %d;\n", iWidth);
    }
    if (iHeight == -1) {
	printf("var iheight = '';\n");
    } else {
	printf("var iheight = %d;\n", iHeight);
    }
    if (iFps == -1) {
	printf("var ifps = '';\n");
    } else {
	printf("var ifps = %d;\n", iFps);
    }
    if (iQuality == -1) {
	printf("var iquality = '';\n");
    } else {
	printf("var iquality = %d;\n", iQuality);
    }
    if (iTcpport == -1) {
	printf("var itcpport = '';\n");
    } else {
	printf("var itcpport = %d;\n", iTcpport);
    }

    GetDriverName(strDriverName, strModulePath);
    iTmp = DetectCam(strDriverName);
    if ( iTmp == 1) {
	printf("var bdetected = true;\n");
	printf("var sdriver = '%s';\n", strDriverName);
    } else {
	printf("var bdetected = false;\n");
	printf("var sdriver = '';\n");
    }

    return iRet;
}

int GetWebcamViewConf()
{
    int iRet=0;
    int iState = 0;
    int iWidth = -1;
    int iHeight = -1;
    int iTcpport = -1;
    char strTmp[256];
    char strCommand[256];
    
    strTmp[0]='\0';
    strCommand[0]='\0';
    
    // Reading webcam parms
    strcpy(str_tag1_name, "webcam");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
        sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
            iState = 1;
        } else {
            iState = 0;
        }

        strcpy(str_attribute_name, "width");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iWidth = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -1;
            }
        }

        strcpy(str_attribute_name, "height");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iHeight = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -2;
            }
        }

        strcpy(str_attribute_name, "tcpport");
        read_attribute();
        if (find_status.value_found == 1) {
            sprintf(strTmp, "%s", str_attribute_value);
            iTcpport = strtol(strTmp, NULL, 10);
            if ((errno == EINVAL) || (errno == ERANGE)) {
	        iRet = -3;
            }
        }
    } else {
        iRet = -4;
    }

    if (iWidth == -1)
	iWidth = 320;
    if (iHeight == -1)
	iHeight = 240;
    if (iTcpport == -1)
	iTcpport = 8888;

    if (iState == 0) {
	printf("webcam_server daemon isn't running\n");
    } else {
        printf("//<!-- hide\n");
    
	printf("document.write('<APPLET code=\"WebCamApplet.class\" archive=\"applet.jar\" ");
        printf("width=\"%d\" height=\"%d\">');\n", iWidth, iHeight);
        printf("document.write('<param name=URL value=\"http://' + location.hostname + ':' + %d + '\">');\n", iTcpport);
        printf("document.write('<param name=FPS value=\"1\">');\n");
        printf("document.write('<param name=width value=\"%d\">');\n", iWidth);
        printf("document.write('<param name=height value=\"%d\">');\n", iHeight);
        printf("document.write('</APPLET>');\n");
        printf("// done hiding -->\n");
    }

    return iRet;
}

int SetWebcamRsiConf(int ArgEnable, char *ArgModulePath, int ArgWAN, char *ArgCaption,
    int ArgWidth, int ArgHeight, int ArgFps, int ArgQuality, int ArgTcpport, int ArgOldTcpport)
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    char strEnable[8];
    char strWAN[8];
    char strCommand[1024];
    
    int iTmp = -1;
    
    int rsiSize = 0;
    char *pc = NULL;
    
    rsiSize = sysGetRsiSize();
    if ((strXmlBuf = malloc(rsiSize + 1)) == NULL)
    {
        printf("Failed to allocate %d bytes of memory.\n", rsiSize);
        return -1;
    }
    memset(strXmlBuf, 0xFF, rsiSize + 1);
    sysRsiGet(strXmlBuf, rsiSize, 0);
    strXmlBuf[rsiSize] = '\0';

    // if <rsitree> cannot be found then return
    if (memcmp(strXmlBuf, XML_RSI_START_TAG, strlen(XML_RSI_START_TAG)) == 0) {
	// determine data length
	pc = strstr(strXmlBuf, XML_RSI_END_TAG);
	if (pc != NULL)
	    xmlCfgLen = pc - strXmlBuf + strlen(XML_RSI_END_TAG) + 1;
        strXmlBuf[xmlCfgLen - 1] = '\0';
    } else  {
	printf("Invalid configuration data.\n");
	free(strXmlBuf);
	return -2;
    }

    if ((xmlCfgLen + MAX_WEBCAM_SECTION_SIZE) > rsiSize) {
	free(strXmlBuf);
	return -3;
    }

    char *ps, *pe;
    char *newRsi;
    long lTmpSize;

    read_section_bounds(strXmlBuf, "webcam", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	free(strXmlBuf);
	return -4;
    }
    while (*(pe + 1) == '\n') pe++;

    newRsi = (char *) malloc(rsiSize);
    memset(newRsi, 0xFF, rsiSize);
    memcpy(newRsi, strXmlBuf, ps - strXmlBuf);
    newRsi[ps - strXmlBuf] = '\0';

    if (ArgEnable == 0) {
	sprintf(strEnable, "disable");
    } else {
    	sprintf(strEnable, "enable");
    }
    if (ArgWAN == 0) {
	sprintf(strWAN, "disable");
    } else {
    	sprintf(strWAN, "enable");
    }

    sprintf(newRsi, "%s<webcam>\n<global state=\"%s\" modulepath=\"%s\" wan=\"%s\" caption=\"%s\" width=\"%d\" height=\"%d\" fps=\"%d\" quality=\"%d\" tcpport=\"%d\" />\n</webcam>\n",
        newRsi, strEnable, ArgModulePath, strWAN, ArgCaption, ArgWidth, ArgHeight, ArgFps, ArgQuality, ArgTcpport);
    
    lTmpSize = strlen(newRsi);
    memcpy(&newRsi[lTmpSize], pe + 1, strXmlBuf + xmlCfgLen - pe - 1);
    newRsi[lTmpSize + strXmlBuf + xmlCfgLen - pe - 1] = '\0';
//    printf("%s\n", newRsi);

    sysRsiSet(newRsi, rsiSize, 0);
        
    free(newRsi);
    free(strXmlBuf);

    if (ArgOldTcpport == -1) {
	iTmp = 8888;
    } else { 
	iTmp = ArgOldTcpport;
    }

    if (verifyWANAccess(iTmp) == 1) {
        sprintf(strCommand, "%s -D INPUT -p tcp --dport %d -j ACCEPT", IPTABLES, iTmp);
	system(strCommand);
    }
    
    system("/usr/bin/killall webcam_server");

    if (strcasecmp(ArgModulePath, "spca5xx") == 0) {
	system("/sbin/rmmod spca5xx");
    } else {
	sprintf(strCommand, "/sbin/rmmod %s", ArgModulePath);
	system(strCommand);
    }
    system("/sbin/rmmod videodev");
    
    // In this case rsiconf starts the daemon
    system("/bin/rsiconf webcam");
    
    return 0;
}

// 0 - no webcam; 1 - webcam detected
int DetectSupportedCam(char *DriverName)
{
    char sRow[1024];
    FILE *fs = NULL;
    int cameraFound = 0;
    int rowFound = 0;
    char *strDriver = NULL;

    if (fileExists(PROC_BUS_USB_DEVICES) == 0) {
        if ((fs=fopen(PROC_BUS_USB_DEVICES, "r")) != NULL) {
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {
		if (cameraFound == 0) {
    		    if (strstr(sRow, "Product=Camera") != NULL) {
			cameraFound = 1;
		    }
		} else {
		    if (sRow[0] == '\0') {
			cameraFound = 0;
		    } else {
			strDriver = strstr(sRow, "Driver=");
    			if (strDriver != NULL) {
			    sprintf(DriverName, "%s", strDriver + 7);
			    if (DriverName[strlen(DriverName) - 1] == 10) {
				DriverName[strlen(DriverName) - 1] = '\0';
			    }
			    rowFound = 1;
			    break;;
			}
		    }
        	}
    	    }
    	    fclose(fs);
	}
    }
    
    return rowFound;
}

// 0 - no webcam; 1 - webcam detected
int DetectCam(char *DriverName)
{
    char sRow[1024];
    FILE *fs = NULL;
    int rowFound = 0;
    char *strDriver = NULL;
    char strDriverRow[256];

    sprintf(strDriverRow, "Driver=%s", DriverName);
	
    if (fileExists(PROC_BUS_USB_DEVICES) == 0) {
        if ((fs=fopen(PROC_BUS_USB_DEVICES, "r")) != NULL) {
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {
		strDriver = strstr(sRow, strDriverRow);
    		if (strDriver != NULL) {
		    rowFound = 1;
		    break;;
        	}
    	    }
    	    fclose(fs);
	}
    }
    
    return rowFound;
}

void GetDriverName(char *DriverName, char *DriverPath)
{
    char *pDriverName = NULL;

    strcpy(DriverName, DriverPath);
    pDriverName = strrchr(DriverName, '/');
    if (pDriverName == NULL) {
	pDriverName = DriverName;
    } else {
	pDriverName++;
    }
    if (strncmp(".ko", &pDriverName[strlen(pDriverName) - 3], 3) == 0) {
	pDriverName[strlen(pDriverName) - 3] == '\0';
    }
}

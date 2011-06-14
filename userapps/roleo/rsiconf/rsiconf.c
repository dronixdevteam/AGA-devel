#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "psixml.h"
#include "nanoxml.h"

#include "rsiconf.h"
#include "rsiconfadsl.h"
#include "../shared/rsi_api.h"
#include "../shared/samba.h"
#include "../shared/util.h"
#include "../shared/passwd.h"

void usage(char *strname)
{
    printf("Usage: %s cmd\n", strname);
}
	    
int main(int argc, char*argv[])
{
    int iRet=0;
    
    if ((argc < 2) || (argc > 3)) {
	usage(argv[0]);
	return -1;
    }
    
    if (strcmp("samba", argv[1])==0) {
	if (configure_samba() == 0) {
	    printf("samba configuration done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -2;
	}
    } else if (strcmp("udhcpd", argv[1])==0) {
	if (configure_udhcpd() == 0) {
	    printf("udhcpd configuration done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -3;
	}
    } else if (strcmp("ftpd", argv[1])==0) {
	if (configure_bftpd() == 0) {
	    printf("ftpd configuration done\n");
	    iRet = 0;
	} else {
	    printf("Error configuring ftp\n");
	    iRet = -3;
	}
    } else if (strcmp("adslctl", argv[1])==0) {
	if ((argc == 3) && (strcasecmp("--force", argv[2])==0)) {
	    if (configure_adslctl(1) == 0) {
		printf("adslctl configuration done\n");
		iRet = 0;
	    } else {
		printf("Missing parameters\n");
		iRet = -4;
	    }
	} else {
	    if (configure_adslctl(0) == 0) {
		printf("adslctl configuration done\n");
		iRet = 0;
	    } else {
		printf("Missing parameters\n");
		iRet = -4;
	    }
	}
    } else if (strcmp("antdiv", argv[1])==0) {
	if (configure_antdiv() == 0) {
	    printf("antenna diversity configuration done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -5;
	}
    } else if (strcmp("printer", argv[1])==0) {
	if (configure_printer() == 0) {
	    printf("printer configuration done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -6;
	}
    } else if (strcmp("profile", argv[1])==0) {
	if (execute_profile() == 0) {
	    printf("profile execution done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -7;
	}
    } else if (strcmp("webcam", argv[1])==0) {
	if (configure_webcam() == 0) {
	    printf("webcam configuration done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -8;
	}
    } else {
	usage(argv[0]);
	iRet = -99;
    }
    
    return iRet;
}

int configure_bftpd()
{
    int iRet=0;
    int iState = 0;
    char strName[NAME_LENGTH];
    char strPassword[PASSWORD_LENGTH];
    char strHome[DIR_LENGTH];
    int iWrite = 0;
    char strTmp[256];
    char strFile[2048];
    int userSupp = 0;
    int userAnon = 0;
    int PasswdLength = 0;
    
    strName[0] = '\0';
    strPassword[0] = '\0';
    strHome[0] = '\0';
    
    strFile[0] = '\0';

    int boo;
    for (boo =1; boo > 0; boo++) {
	// Reading ftpd entry
	strcpy(str_tag1_name, "ftpd");
	sprintf(str_tag2_name, "user%d", boo);
        strcpy(str_attribute_name, "state");
        read_attribute();
        if (find_status.value_found == 1) {
	    sprintf(strTmp, "%s", str_attribute_value);
	    if (strcasecmp("enable", strTmp) == 0) {
	        iState = 1;
	    } else {
	        iState = 0;
	    }

            strcpy(str_attribute_name, "name");
            read_attribute();
            if (find_status.value_found == 1) {
        	sprintf(strName, "%s", str_attribute_value);
	    }

            strcpy(str_attribute_name, "password");
            read_attribute();
            if (find_status.value_found == 1) {
		base64Decode(strPassword, str_attribute_value, &PasswdLength);
//        	sprintf(strPassword, "%s", str_attribute_value);
	    }
	    
            strcpy(str_attribute_name, "home");
            read_attribute();
            if (find_status.value_found == 1) {
		sprintf(strHome, "%s", str_attribute_value);
	    }

            strcpy(str_attribute_name, "write");
            read_attribute();
            if (find_status.value_found == 1) {
		sprintf(strTmp, "%s", str_attribute_value);
		if (strcasecmp("yes", strTmp) == 0) {
		    iWrite = 1;
		} else {
		    iWrite = 0;
		}
	    }

	    if (strcmp("support", strName) == 0) {
		// Support user
		userSupp = 1;
		sprintf(strFile, "%s\n\nuser support {\n", strFile);
		if (iState == 1) {
		    sprintf(strFile, "%s  ANONYMOUS_USER=\"no\"\n", strFile);
		    sprintf(strFile, "%s  ROOTDIR=\"%s\"\n", strFile, strHome);
		    if (iWrite == 1) {
			sprintf(strFile, "%s  ALLOWCOMMAND_DELE=\"yes\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_STOR=\"yes\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_SITE=\"yes\"\n", strFile);
		    } else {
			sprintf(strFile, "%s  ALLOWCOMMAND_DELE=\"no\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_STOR=\"no\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_SITE=\"no\"\n", strFile);
		    }
		} else {
		    sprintf(strFile, "%s  DENY_LOGIN=\"login not allowed.\"\n", strFile);
		}    
		sprintf(strFile, "%s}",strFile);

	    } else if (strcmp("anonymous", strName) == 0) {
		// Anonymous user
		userAnon = 1;
		sprintf(strFile, "%s\n\nuser ftp {\n", strFile);
		if (iState == 1) {
		    sprintf(strFile, "%s  ANONYMOUS_USER=\"yes\"\n", strFile);
		    sprintf(strFile, "%s  ROOTDIR=\"%s\"\n", strFile, strHome);
		    if (iWrite == 1) {
			sprintf(strFile, "%s  ALLOWCOMMAND_DELE=\"yes\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_STOR=\"yes\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_SITE=\"yes\"\n", strFile);
		    } else {
			sprintf(strFile, "%s  ALLOWCOMMAND_DELE=\"no\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_STOR=\"no\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_SITE=\"no\"\n", strFile);
		    }
		} else {
		    sprintf(strFile, "%s  DENY_LOGIN=\"login not allowed.\"\n", strFile);
		}    
		sprintf(strFile, "%s}",strFile);
		sprintf(strFile, "%s\n\nuser anonymous {\n  ALIAS=\"ftp\"\n}\n", strFile);
		append_user("ftp", "", 100 + boo, 65534, "ftp user", "/tmp", "/bin/false");

	    } else {
		// Generic user
		if (iState == 1) {
		    sprintf(strFile, "%s\n\nuser %s {\n", strFile, strName);
		    sprintf(strFile, "%s  ANONYMOUS_USER=\"no\"\n", strFile);
		    sprintf(strFile, "%s  ROOTDIR=\"%s\"\n", strFile, strHome);
		    if (iWrite == 1) {
			sprintf(strFile, "%s  ALLOWCOMMAND_DELE=\"yes\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_STOR=\"yes\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_SITE=\"yes\"\n", strFile);
		    } else {
			sprintf(strFile, "%s  ALLOWCOMMAND_DELE=\"no\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_STOR=\"no\"\n", strFile);
			sprintf(strFile, "%s  ALLOWCOMMAND_SITE=\"no\"\n", strFile);
		    }
		    sprintf(strFile, "%s}",strFile);
		    append_user(strName, strPassword, 100 + boo, 65534, "ftp user", strHome, "/bin/false");
		}    
	    }
	    
	} else {
	    boo=-1;
	}
    }

    // Se manca anche solo un utente qualcosa non va nella configurazione
    if ((userSupp == 0) || (userAnon == 0)) {

	AddDefaultFtpdEntries();
	
	sprintf(strFile, "%s\n\nuser support {\n", strFile);
	sprintf(strFile, "%s  DENY_LOGIN=\"login not allowed.\"\n", strFile);
	sprintf(strFile, "%s}",strFile);

	sprintf(strFile, "%s\n\nuser ftp {\n", strFile);
	sprintf(strFile, "%s  DENY_LOGIN=\"login not allowed.\"\n", strFile);
	sprintf(strFile, "%s}",strFile);
	sprintf(strFile, "%s\n\nuser anonymous {\n  ALIAS=\"ftp\"\n}\n", strFile);
    }

    fileCopy(ETCBFTPDCONFDEFAULT, VARBFTPDCONF);
    appendToTextFile(VARBFTPDCONF, strFile);

    return iRet;
}

// Questa funzione si limita a leggere la configurazione rsitree e a creare con la
// SetSambaConf un file /var/samba/smb.conf piu' o meno configurato.
// Mancano comunque le eventuali mount di dischi usb.
int configure_samba()
{
    int iRet = 0;
    int iState;
    char strWorkName[MAX_STRING_SIZE];
    char strServerName[MAX_STRING_SIZE];
    char strServerDesc[MAX_STRING_SIZE];
    int iRootShare;
    char strTmp[MAX_STRING_SIZE];
    
    iState=0;
    strWorkName[0] = '\0';
    strServerName[0] = '\0';
    strServerDesc[0] = '\0';
    iRootShare = 0;

    strTmp[0]='\0';
    
    strcpy(str_tag1_name, "samba");
    
    // Reading samba global parameters: state, workgroup, netbios_name, etc...
    // Mandatory parameters
    strcpy(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
            iState = 1;
        }
    } else {
	iRet = -1;
    }
    strcpy(str_attribute_name, "workgroup");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strWorkName, "%s", str_attribute_value);
//        printf("%s\n", str_attribute_value);
    } else {
	iRet = -2;
    }
    strcpy(str_attribute_name, "netbios_name");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strServerName, "%s", str_attribute_value);
//        printf("%s\n", str_attribute_value);
    } else {
	iRet = -3;
    }
    strcpy(str_attribute_name, "description");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strServerDesc, "%s", str_attribute_value);
//        printf("%s\n", str_attribute_value);
    } else {
	iRet = -4;
    }
    strcpy(str_attribute_name, "share_root");
    read_attribute();
    if (find_status.value_found == 1) {
	if ((str_attribute_value[0] == 'y') || (str_attribute_value[0] == 'Y')) {
	    iRootShare = 1;
	} else {
	    iRootShare = 0;
	}
//        printf("%s\n", str_attribute_value);
    } else {
	iRet = -5;
    }

    if (iRet == 0) {
	sprintf(strTmp, "echo %d > %s", iState, SAMBA_ENABLED);
	system(strTmp);

	if (SetSambaConf(strWorkName, strServerName, strServerDesc, iRootShare) < 0)
	    iRet = -6;
    }
    
    return iRet;
}

int configure_udhcpd()
{
    int iRet=0;
    char strMac[MAC_LENGTH];
    char strIP[IP_LENGTH];
    FILE *fUdhcpd;
    
    strMac[0]='\0';
    strIP[0]='\0';

    fUdhcpd = fopen(UDHCPD_FILE, "wb");
    if (fUdhcpd == NULL) {
	return -1;
    }
	
    int boo;
    for (boo =1; boo > 0; boo++) {
	// Reading udhcpd static leases: mac, ip
	strcpy(str_tag1_name, "udhcpd");
	sprintf(str_tag2_name, "static%d", boo);
	strcpy(str_attribute_name, "mac");
	read_attribute();
	if (find_status.value_found == 1) {
	    sprintf(strMac, "%s", str_attribute_value);
	    
	    strcpy(str_attribute_name, "ip");
	    read_attribute();
	    if (find_status.value_found == 1) {
		sprintf(strIP, "%s", str_attribute_value);

    		fprintf(fUdhcpd, "static_lease %s %s\n", strMac, strIP);
		
            } else {
        	boo=-1;
	    }
	} else {
            boo=-1;
	}
    }
    
    fclose(fUdhcpd);
    
    return iRet;
}

int configure_antdiv()
{
    int iRet = 0;
    int state = 0;
    char strTmp[256];
    char strCommand[256];
    
    strTmp[0] = '\0';
    strCommand[0] = '\0';
    
    // Reading wlan configuration
    strcpy(str_tag1_name, "wlan");
    sprintf(str_tag2_name, "diversity");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
        sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
	    state = 1;
	} else {
	    return 0;
	}

	sprintf(strCommand, "%s ucantdiv 1", WLCTL);
	system(strCommand);
	sprintf(strCommand, "%s antdiv 3", WLCTL);
	system(strCommand);
	sprintf(strCommand, "%s txant 3", WLCTL);
	system(strCommand);
    
    } else {
	iRet = -1;
    }
    
    return iRet;
}

int configure_printer()
{
    int iRet = 0;
    int state = 0;
    char strTmp[256];
    char strCommand[256];
    
    strTmp[0] = '\0';
    strCommand[0] = '\0';
    
    // Reading printer configuration
    strcpy(str_tag1_name, "printer");
    sprintf(str_tag2_name, "p910nd");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
        sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
	    state = 1;
	} else {
	    return 0;
	}

	sprintf(strCommand, "/bin/p910nd -f /dev/printer0 -b &");
	system(strCommand);
    
    } else {
	iRet = -1;
    }
    
    return iRet;
}

int execute_profile()
{
    int iRet = 0;
    int state = 0;
    char strScript[20480];
    char strTmp[256];
    char strCommand[256];
    FILE *fs;
        
    strTmp[0] = '\0';
    strCommand[0] = '\0';
    
    // Reading profile parms
    strcpy(str_tag1_name, "profile");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
        sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
	    state = 1;
	} else {
	    return 0;
	}

        strcpy(str_attribute_name, "script");
        read_attribute_big();
        if (find_status.value_found == 1) {
    	    sprintf(strScript, "%s", str_attribute_value_big);
	}
	unescape_url(strScript);
	
        if ((fs=fopen(VARPROFILE, "wb")) != NULL) {
            fwrite(strScript, 1, strlen(strScript), fs);
            fclose(fs);

	    sprintf(strCommand, "/bin/sh %s", VARPROFILE);
	    system(strCommand);
	} else {
	    iRet = -1;
	}

    } else {
	iRet = -2;
    }
    
    return iRet;
}

int configure_webcam()
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
    int iTmp = -1;
    char strTmp[256];
    char strCommand[512];
    
    strModulePath[0]='\0';;
    strCaption[0]='\0';
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
            return 0;
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

    if (iRet == 0) {
	sprintf(strCommand, "/sbin/insmod %s/media/video/videodev.ko", DRIVERS_DIR);
	system(strCommand);
	unescape_url(strModulePath);
	if (strchr(strModulePath, '/') == NULL) {
	    if (strncmp(".ko", &strModulePath[strlen(strModulePath) - 3], 3) == 0) {
		sprintf(strCommand, "/sbin/insmod %s/%s", USB_MEDIA_DRIVERS_DIR, strModulePath);
	    } else {
//	if (strcasecmp(strModulePath, "spca5xx") == 0) {
		sprintf(strCommand, "/sbin/insmod %s/%s.ko", USB_MEDIA_DRIVERS_DIR, strModulePath);
	    }
	} else {
	    sprintf(strCommand, "/sbin/insmod %s", strModulePath);
	}
	system(strCommand);
	
	sprintf(strCommand, "/bin/webcam_server -s");
	
	unescape_url(strCaption);
	if (strcasecmp(strCaption, "default") != 0) {
	    if (strcasecmp(strCaption, "none") == 0) {
		sprintf(strCommand, "%s -c \"\"", strCommand);
	    } else {
		sprintf(strCommand, "%s -c \"%s\"", strCommand, strCaption);
	    }
	}
	if ((iWidth != -1) && (iHeight != -1))
	    sprintf(strCommand, "%s -g %dx%d", strCommand, iWidth, iHeight);
	if (iFps != -1)
	    sprintf(strCommand, "%s -mf %d", strCommand, iFps);
	if (iQuality != -1)
	    sprintf(strCommand, "%s -q %d", strCommand, iQuality);
	if (iTcpport != -1)
	    sprintf(strCommand, "%s -p %d", strCommand, iTcpport);
	
	system(strCommand);
	
	if (iTcpport == -1) {
	    iTmp = 8888;
	} else {
	    iTmp = iTcpport;
	}
	
	// Se la porta è aperta e iWAN = 0 bisogna chiuderla
	if ((verifyWANAccess(iTcpport) == 1) && (iWAN == 0)) {
	    sprintf(strCommand, "%s -D INPUT -p tcp --dport %d -j ACCEPT", IPTABLES, iTmp);
	    system(strCommand);
	}
	// Se la porta è chiusa e iWAN = 1 bisogna aprirla
	if ((verifyWANAccess(iTcpport) == 0) && (iWAN == 1)) {
	    sprintf(strCommand, "%s -I INPUT -p tcp --dport %d -j ACCEPT", IPTABLES, iTmp);
	system(strCommand);
	}
    }

    return iRet;
}

int AddDefaultFtpdEntries()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;
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

    if ((xmlCfgLen + MAX_FTPD_ROW_SIZE) > rsiSize) {
	free(strXmlBuf);
	return -3;
    }

    char *ps, *pe;
    char *newRsi;
    long lTmpSize;

    read_section_bounds(strXmlBuf, "ftpd", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	free(strXmlBuf);
	return -4;
    }
    while (*pe != '<') pe--;

    newRsi = (char *) malloc(rsiSize);
    memset(newRsi, 0xFF, rsiSize);
    memcpy(newRsi, strXmlBuf, pe - strXmlBuf);
    newRsi[pe - strXmlBuf] = '\0';
        
    sprintf(newRsi, "%s<user1 state=\"disable\" name=\"support\" home=\"/tmp\" write=\"no\" />\n", newRsi);
    sprintf(newRsi, "%s<user2 state=\"disable\" name=\"anonymous\" home=\"/tmp\" write=\"no\" />\n", newRsi);
    
    lTmpSize = strlen(newRsi);
    memcpy(&newRsi[lTmpSize], pe, strXmlBuf + xmlCfgLen - pe);
    newRsi[lTmpSize + strXmlBuf + xmlCfgLen - pe] = '\0';

    sysRsiSet(newRsi, rsiSize, 0);
        
    free(newRsi);
    free(strXmlBuf);
    
    return 0;
}

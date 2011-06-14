#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <psixml.h>
#include "nanoxml.h"

#include "killprocess.h"
#include "rsi_api.h"
#include "samba.h"
#include "util.h"

int SetSambaConf(char *ArgWorkName, char *ArgServerName, char *ArgServerDesc, int ArgRootShare)
{
    char SambaWorkName[MAX_STRING_SIZE];
    char SambaServerName[MAX_STRING_SIZE];
    char SambaServerDesc[MAX_STRING_SIZE];
    int SambaRootShare = 0;
    
    int iRet=0;
    FILE *fs;
    char sRow[MAX_ROW_SIZE], sRowCopy[MAX_ROW_SIZE];
    char *stokName, *stokValue;
    struct stat s;
    char *fileToSave;
    char *index;
    int fileToSaveMaxSize;
    int writeRow;
    char sCurrentSection[MAX_STRING_SIZE];
    int sectionGlobalPresent = 0;
    int sectionRootPresent = 0;
    char strTmp[MAX_STRING_SIZE];
    
    if ((ArgWorkName == NULL) || (ArgServerName == NULL) || (ArgServerDesc == NULL))
	return -1;

    sprintf(SambaWorkName, ArgWorkName);
    sprintf(SambaServerName, ArgServerName);
    sprintf(SambaServerDesc, ArgServerDesc);
    SambaRootShare = ArgRootShare;
    
    fileCopy(ETC_SMB_CONF_DEFAULT, VAR_SMB_CONF);
    
    if (stat(VAR_SMB_CONF, &s) == 0) {
	// Dimensione del file = dimensione attuale + l'eventuale inserimento
	// di 3 righe + l'eventuale inserimento della share /
	fileToSaveMaxSize = MAX_STRING_SIZE * 3 + MAX_ROOTSHARE_SIZE + s.st_size;
	fileToSave = (char *) malloc(fileToSaveMaxSize * sizeof(char));
	memset(fileToSave, 0, fileToSaveMaxSize);
	index = fileToSave;

	if ((fs=fopen(VAR_SMB_CONF, "r")) != NULL) {
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {

		writeRow = 1;
		strncpy(sRowCopy, sRow, sizeof(sRow));
		stokName = strtok(sRowCopy, "=");
		if (stokName != NULL) {
		    stokValue = strtok(NULL, "\n");

		    stokName = trim(stokName);

		    if ((stokName[0] == '#') || (stokName[0] == ';')) {
			if (writeRow == 1) {
			    memcpy(index, sRow, strlen(sRow));
			    index += strlen(sRow);
			}    
			continue;
		    }

		    if (stokName[0] == '[') {
			sprintf(sCurrentSection, strtok(stokName, "[]"));
			if (strcasecmp("global", sCurrentSection) == 0) {
			    sectionGlobalPresent = 1;
			    if (writeRow == 1) {
				memcpy(index, sRow, strlen(sRow));
				index += strlen(sRow);
			    }    
			} else if (strcasecmp("root", sCurrentSection) == 0) {
			    sectionRootPresent = 1;
			    if ((writeRow == 1) && (SambaRootShare == 1)) {
				memcpy(index, sRow, strlen(sRow));
				index += strlen(sRow);
			    }
			} else {
			    if (writeRow == 1) {
				memcpy(index, sRow, strlen(sRow));
				index += strlen(sRow);
			    }    
			}
			
			continue;
		    }

		    if ((strcasecmp("global", sCurrentSection) == 0) &&
			(strcasecmp("workgroup", stokName) == 0)) {
			
			stokValue = trim(stokValue);
			if (stokValue != NULL) {
			    sprintf(strTmp, "   workgroup = %s\n", SambaWorkName);
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			}
		    } else if ((strcasecmp("global", sCurrentSection) == 0) &&
			(strcasecmp("netbios name", stokName) == 0)) {

			stokValue = trim(stokValue);
			if (stokValue != NULL) {
			    sprintf(strTmp, "   netbios name = %s\n", SambaServerName);
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			}
		    } else if ((strcasecmp("global", sCurrentSection) == 0) &&
			(strcasecmp("server string", stokName) == 0)) {

			stokValue = trim(stokValue);
			if (stokValue != NULL) {
			    sprintf(strTmp, "   server string = %s\n", SambaServerDesc);
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			}
		    } else if ((strcasecmp("root", sCurrentSection) == 0) &&
			(strcasecmp("path", stokName) == 0)) {
			
			stokValue = trim(stokValue);
			if (stokValue != NULL) {
			    if (SambaRootShare == 1) {
				sprintf(strTmp, "   path = /\n");
				memcpy(index, strTmp, strlen(strTmp));
				index += strlen(strTmp);
				writeRow = 0;
			    } else {
				writeRow = 0;
			    }
			}			
		    } else if ((strcasecmp("root", sCurrentSection) == 0) &&
			(strcasecmp("public", stokName) == 0)) {
			
			if (SambaRootShare == 1) {
			    sprintf(strTmp, "   public = yes\n");
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			} else {
			    writeRow = 0;
			}
		    } else if ((strcasecmp("root", sCurrentSection) == 0) &&
			(strcasecmp("writable", stokName) == 0)) {
			
			if (SambaRootShare == 1) {
			    sprintf(strTmp, "   writable = yes\n");
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			} else {
			    writeRow = 0;
			}
		    } else if ((strcasecmp("root", sCurrentSection) == 0) &&
			(strcasecmp("printable", stokName) == 0)) {
			
			if (SambaRootShare == 1) {
			    sprintf(strTmp, "   printable = no\n");
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			} else {
			    writeRow = 0;
			}
		    } else if ((strcasecmp("root", sCurrentSection) == 0) &&
			(strcasecmp("guest ok", stokName) == 0)) {
			
			if (SambaRootShare == 1) {
			    sprintf(strTmp, "   guest ok = yes\n");
			    memcpy(index, strTmp, strlen(strTmp));
			    index += strlen(strTmp);
			    writeRow = 0;
			} else {
			    writeRow = 0;
			}
		    }
		}
		
		if (writeRow == 1) {
		    memcpy(index, sRow, strlen(sRow));
		    index += strlen(sRow);
		}
	    }
	    fclose(fs);

	    if (sectionGlobalPresent == 0) {
		// in questo caso cancello fileToSave
		memset(fileToSave, 0, fileToSaveMaxSize);
		index = fileToSave;
		memcpy(index, "[global]\n", 9);
		index += 9;
		sprintf(strTmp, "   workgroup = %s\n", SambaWorkName);
		memcpy(index, strTmp, strlen(strTmp));
		index += strlen(strTmp);
		sprintf(strTmp, "   netbios name = %s\n", SambaServerName);
		memcpy(index, strTmp, strlen(strTmp));
		index += strlen(strTmp);
		sprintf(strTmp, "   server string = %s\n", SambaServerDesc);
		memcpy(index, strTmp, strlen(strTmp));
		index += strlen(strTmp);
		memcpy(index, "\n", 1);
		index += 1;
	    }
	    if ((sectionRootPresent == 0) && (SambaRootShare == 1)) {
		memcpy(index, "[root]\n", 7);
		index += 7;
		memcpy(index, "   path = /\n", 12);
		index += 12;
		memcpy(index, "   public = yes\n", 16);
		index += 16;
		memcpy(index, "   writable = yes\n", 18);
		index += 18;
		memcpy(index, "   printable = no\n", 18);
		index += 18;
		memcpy(index, "   guest ok = yes\n", 18);
		index += 18;
		memcpy(index, "\n\n", 2);
		index += 2;
	    }    
	    if ((fs=fopen(VAR_SMB_CONF, "wb")) != NULL) {
		int iCont;
		for (iCont = strlen(fileToSave) - 1; iCont >= 1; iCont--) {
		    if (fileToSave[iCont-1] != 10)
			break;
		    if ((fileToSave[iCont] == 10) &&
			(fileToSave[iCont-1] == 10)) {
			    
			fileToSave[iCont] = '\0';
		    }
		}
		fwrite(fileToSave, 1, strlen(fileToSave), fs);
		fclose(fs);
	    } else {
		iRet = -4;
	    }
	} else {
	    iRet = -3;
	}
	
	free(fileToSave);	
    } else {
        iRet = -2;
    }

    return iRet;    
}

int GetSambaConf()
{
    int iRet = 0;
    int iState;
    char strWorkName[MAX_STRING_SIZE];
    char strServerName[MAX_STRING_SIZE];
    char strServerDesc[MAX_STRING_SIZE];
    int iRootShare;
    char strTmp[MAX_STRING_SIZE];
    
    iState=0;
    strWorkName[0]='\0';
    strServerName[0]='\0';
    strServerDesc[0]='\0';
    iRootShare=0;

    strTmp[0]='\0';
    
    strcpy(str_tag1_name, "samba");
    
    // Reading samba global parameters: workgroup, netbios_name
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
    
    if (iState == 0) {
        printf("var ena = false;\n");
    } else {
        printf("var ena = true;\n");
    }
    printf("var wn = '%s';\n", strWorkName);
    printf("var sn = '%s';\n", strServerName);
    printf("var sd = '%s';\n", strServerDesc);
    if (iRootShare == 0) {
        printf("var rs = false;\n");
    } else {
        printf("var rs = true;\n");
    }
    
    return iRet;
}

int GetSambaStart()
{
    int iRet = 0;
    char strTmp[MAX_STRING_SIZE];
    
    strTmp[0]='\0';

    strcpy(str_tag1_name, "samba");
    
    // Reading samba global parameters: state
    strcpy(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strTmp, "%s", str_attribute_value);
        if (strcasecmp("enable", strTmp) == 0) {
            iRet = 1;
        } else {
            iRet = 0;
        }
    } else {
	iRet = -1;
    }
    
    return iRet;
}

int SetSambaRsiConf(int ArgState, char *ArgWorkName, char *ArgServerName, char *ArgServerDesc, int ArgRootShare)
//int main(int argc, char *argv[])
{
/*
    char ArgWorkName[256];
    char ArgServerName[256];
    char ArgServerDesc[256];
    int ArgRootShare;
    
    sprintf(ArgWorkName, "%s", argv[1]);
    sprintf(ArgServerName, "%s", argv[2]);
    sprintf(ArgServerDesc, "%s", argv[3]);
    ArgRootShare = atoi(argv[4]);
*/

    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int rsiSize = 0;
    char *pc = NULL;
    char sCommand[64];
    
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

    if ((xmlCfgLen + MAX_SAMBA_SECTION_SIZE) > rsiSize) {
	free(strXmlBuf);
	return -3;
    }

    char *ps, *pe;
    char *newRsi;
    long lTmpSize;

    read_section_bounds(strXmlBuf, "samba", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	free(strXmlBuf);
	return -4;
    }
    while (*(pe + 1) == '\n') pe++;

    newRsi = (char *) malloc(rsiSize);
    memset(newRsi, 0xFF, rsiSize);
    memcpy(newRsi, strXmlBuf, ps - strXmlBuf);
    newRsi[ps - strXmlBuf] = '\0';

    if (ArgState == 0) {
	if (ArgRootShare == 0) {
	    sprintf(newRsi, "%s<samba>\n<global state=\"disable\" workgroup=\"%s\" netbios_name=\"%s\" description=\"%s\" share_root=\"no\" />\n</samba>\n",
		newRsi, ArgWorkName, ArgServerName, ArgServerDesc);
	} else {
	    sprintf(newRsi, "%s<samba>\n<global state=\"disable\" workgroup=\"%s\" netbios_name=\"%s\" description=\"%s\" share_root=\"yes\" />\n</samba>\n",
		newRsi, ArgWorkName, ArgServerName, ArgServerDesc);
	}
    } else {
	if (ArgRootShare == 0) {
	    sprintf(newRsi, "%s<samba>\n<global state=\"enable\" workgroup=\"%s\" netbios_name=\"%s\" description=\"%s\" share_root=\"no\" />\n</samba>\n",
		newRsi, ArgWorkName, ArgServerName, ArgServerDesc);
	} else {
	    sprintf(newRsi, "%s<samba>\n<global state=\"enable\" workgroup=\"%s\" netbios_name=\"%s\" description=\"%s\" share_root=\"yes\" />\n</samba>\n",
		newRsi, ArgWorkName, ArgServerName, ArgServerDesc);
	}
    }
    
    lTmpSize = strlen(newRsi);
    memcpy(&newRsi[lTmpSize], pe + 1, strXmlBuf + xmlCfgLen - pe - 1);
    newRsi[lTmpSize + strXmlBuf + xmlCfgLen - pe - 1] = '\0';
//    printf("%s\n", newRsi);

    sysRsiSet(newRsi, rsiSize, 0);
        
    free(newRsi);
    free(strXmlBuf);

    system("/bin/rsiconf samba");

    killProcess("smbd", SMBD_LOCK_FILE);
    killProcess("nmbd", NMBD_LOCK_FILE);
    
    configureOtherSambaMounts();

    if (ArgState == 1) {
	sprintf(sCommand, "/bin/smbd -D");
	system(sCommand);
	sprintf(sCommand, "/bin/nmbd -D");
	system(sCommand);
    }
    
    return 0;
}

int configureOtherSambaMounts()
{
    int iRet=0;
    FILE *fs;
    char sMDev[64], sMPoint[64];
    char s1[64], s2[64], s3[64], s4[64];
    char *pTmp;
    char strUpdateSmbConf[MAX_SMB_UPDATE_SIZE];
    int numberOfMounts = 0;

    strUpdateSmbConf[0]='\0';

    if ((fs=fopen("/proc/mounts","r")) != NULL) {
        while (fscanf(fs, "%s%s%s%s%s%s", sMDev, sMPoint, s1, s2, s3, s4) != EOF) {
	    //printf ("%s %s\n", sMDev, sMPoint);
	    if (strncmp(sMPoint, "/var/mounts", 11) == 0) {
		pTmp = strrchr(sMPoint, '/') + 1;
		sprintf(strUpdateSmbConf, "%s[%s]\n", strUpdateSmbConf, pTmp);
		sprintf(strUpdateSmbConf, "%s   path = %s\n   public = yes\n   writable = yes\n   printable = no\n   guest ok = yes\n\n",
		    strUpdateSmbConf, sMPoint);
		numberOfMounts++;
	    }
	}
	fclose(fs);
    } else {
	iRet = -1;
    }

    if (numberOfMounts > 0) {
	if (appendToTextFile(VAR_SMB_CONF, strUpdateSmbConf) < 0)
	    iRet=-2;
    }
    
    if (iRet == 0)
	iRet = numberOfMounts;
	 
    return iRet;
}

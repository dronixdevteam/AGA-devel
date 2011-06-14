#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <fcntl.h>
#include <psixml.h>
#include "nanoxml.h"

#include "hotplug.h"
#include "../shared/samba.h"
#include "../shared/killprocess.h"
#include "../shared/rsi_api.h"

int main(int argc, char *argv[])
{
    int iRet = 0;
    char sAction[256];
    char sDev[256];
    char sDir[256];
    char sCommand[256];
    char sTmp[256];
    char *pTmp;
    mode_t perms = 0777;
    char sLog[256];
    int iDevNum = 0;
    
    if (argc >= 2) {
	
	sprintf(sLog, "ARG: %s\n", argv[1]);
	
	if (strcasecmp(argv[1], "BLOCK")==0) {
	    pTmp = getenv("ACTION");
	    if ((pTmp != NULL) && (strcmp(pTmp, "") != 0)) {
		strcpy(sAction, pTmp);

		// fill log string
	        sprintf(sLog, "%sACTION: %s\n", sLog, sAction);
		
		// ACTION ADD
		if (strcasecmp(sAction, "add") == 0) {
		    pTmp = getenv("DEVPATH");
		    if ((pTmp != NULL) && (strcmp(pTmp, "") != 0)) {

			strcpy(sDev, pTmp);

			// print log
		        sprintf(sLog, "%sDEV: %s\n", sLog, sDev);
			writeLog(sLog);

			if ((sDev[strlen(sDev)-1] >= '0') &&
			    (sDev[strlen(sDev)-1] <= '9')) {
			    
			    iDevNum = (int) (sDev[strlen(sDev)-1]) - 48;
			    sleep(iDevNum);
			    sprintf(sTmp, "Device n. %d\n", iDevNum);
			    writeLog(sTmp);
			    
			    pTmp = strrchr(sDev, '/') + 1;
			    sprintf(sDev, "/dev/%s", pTmp);
			    sprintf(sDir, "%s/%s", MOUNTDIR, pTmp);
			    //printf("%s\n", sDev);

			    mkdir(MOUNTDIR, perms);
			    mkdir(sDir, perms);

//			    // Try automount NTFS3G
//			    sprintf(sCommand, "%s %s %s", MOUNTNTFS3G, sDev, sDir);
//			    system(sCommand);

			    // Try automount
			    sprintf(sCommand, "%s %s %s", MOUNT, sDev, sDir);
			    system(sCommand);
			    
			    sprintf(sTmp, "%s\n", sCommand);
			    writeLog(sTmp);			    

			    // SAMBA
			    // Testing semaphore for multiple partitions
			    FILE *fsSem;
			    if ((fsSem=fopen(SMBSEMFILE,"r")) == NULL) {

				// Creating semaphore for multiple partitions
				fsSem=fopen(SMBSEMFILE,"w");
				fclose(fsSem);

				killProcess("smbd", SMBDLOCKFILE);
				killProcess("nmbd", NMBDLOCKFILE);
				sleep(5);
				
				remove(VARSMBCONF);
//				if (fileExists(SDA1VARSMBCONF) == 0) {
//				    
//				    sprintf(sCommand, "cp %s %s",
//					SDA1VARSMBCONF, VARSMBCONF);				
//				} else {
				    sprintf(sCommand, "cp %s %s",
					ETCSMBCONFDEF, VARSMBCONF);
//				}
				system(sCommand);			    

				sprintf(sCommand, "/bin/rsiconf samba");
				system(sCommand);			    
				
				configureOtherSambaMounts();
				if (GetSambaStart() == 1) {
				    sprintf(sCommand, "%s -D", SMBD);
				    system(sCommand);
				    sprintf(sCommand, "%s -D", NMBD);
				    system(sCommand);
				}
				
				// Remove semaphore
				remove(SMBSEMFILE);
			    } else {
    				fclose(fsSem);
			    }
			}
		    } else {
			iRet = -3;
		    }

		// ACTION REMOVE
		} else if (strcasecmp(sAction, "remove") == 0) {
		    pTmp = getenv("DEVPATH");
		    if ((pTmp != NULL) && (strcmp(pTmp, "") != 0)) {
			strcpy(sDev, pTmp);

			// print log
			sprintf(sLog, "%sDEV: %s\n", sLog, sDev);
			writeLog(sLog);

			if ((sDev[strlen(sDev)-1] >= '0') &&
			    (sDev[strlen(sDev)-1] <= '9')) {
			    
			    iDevNum = (int) (sDev[strlen(sDev)-1]) - 48;
			    sleep(iDevNum);
			    sprintf(sTmp, "Device n. %d\n", iDevNum);
			    writeLog(sTmp);

			    pTmp = strrchr(sDev, '/') + 1;
			    sprintf(sDev, "/dev/%s", pTmp);
			    sprintf(sDir, "%s/%s", MOUNTDIR, pTmp);
			    //printf("%s\n", sDev);
			    
			    // SAMBA
			    // Testing semaphore for multiple partitions
			    FILE *fsSem;
			    if ((fsSem=fopen(SMBSEMFILE,"r")) == NULL) {

				// Creating semaphore for multiple partitions
				fsSem=fopen(SMBSEMFILE,"w");
				fclose(fsSem);

				killProcess("smbd", SMBDLOCKFILE);
				killProcess("nmbd", NMBDLOCKFILE);

				sprintf(sCommand, "%s %s", UMOUNT, sDev);
				system(sCommand);
				rmdir(sDir);

				sleep(5);

				remove(VARSMBCONF);
//				if (fileExists(SDA1VARSMBCONF) == 0) {
//				    
//				    sprintf(sCommand, "cp %s %s",
//					SDA1VARSMBCONF, VARSMBCONF);				
//				} else {
				    sprintf(sCommand, "cp %s %s",
					ETCSMBCONFDEF, VARSMBCONF);
//				}
				system(sCommand);

				sprintf(sCommand, "/bin/rsiconf samba");
				system(sCommand);
				
				configureOtherSambaMounts();
				if (GetSambaStart() == 1) {
				    sprintf(sCommand, "%s -D", SMBD);
				    system(sCommand);
				    sprintf(sCommand, "%s -D", NMBD);
				    system(sCommand);
				}
				
				// Remove semaphore
				remove(SMBSEMFILE);
			    } else {
    				fclose(fsSem);
			    }

			    sprintf(sCommand, "%s %s", UMOUNT, sDev);
			    system(sCommand);
			    rmdir(sDir);

			    sprintf(sTmp, "%s\n", sCommand);
			    writeLog(sTmp);			    
			}
		    } else {
			iRet = -3;
		    }
		}
	    } else {
		iRet = -2;
	    }
	}
	sprintf(sCommand, "%s %s", ORIGINALHOTPLUG, argv[1]);
	system(sCommand);	

    } else {
	sprintf(sCommand, "%s", ORIGINALHOTPLUG);
	system(sCommand);	
	iRet = -1;
    }

    return iRet;
}

int writeLog(char *logRow)
{
    int iRet;
    struct stat s;
    FILE *fsLog;
    
    // log debug messages only if /var/hotplug.log exists
    if (stat(LOGFILE, &s) == 0) {
	if ((fsLog=fopen(LOGFILE,"a")) != NULL) {
	    fprintf(fsLog, "%s", logRow);
    	    fclose(fsLog);
	    iRet = 0;
	} else {
	    iRet = -2;
	}
    } else {
	iRet = -1;
    }
    
    return iRet;
}

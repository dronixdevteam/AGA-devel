#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include "killprocess.h"

int killProcess(char *processName, char *pidName)
{
    FILE *fs;
    int psPid;
    char sTmp[64];
    int counter;
    int iResult = 0;
    int iRet = 0;
    
    if (pidName == NULL) {
	sprintf(sTmp, "%s/%s.pid", PIDDIR, processName);
    } else {
	sprintf(sTmp, "%s", pidName);
    }
    if ((fs=fopen(sTmp,"r")) != NULL) {
	iResult = fscanf(fs, "%d", &psPid);
	fclose(fs);
	if (iResult != 0) {
	    kill(psPid, SIGTERM);
	    counter = 0;
	    while (counter++ < 5) {
		if (waitpid(psPid, NULL, WNOHANG) > 0)
		    break;
		sleep(1);
	    }
	    if (waitpid(psPid, NULL, WNOHANG) == 0) {
		kill(psPid, SIGKILL);
	    }
	} else {
	    iRet = -2;
	}	
    } else {
	iRet = -1;
    }
    
    return iRet;
}


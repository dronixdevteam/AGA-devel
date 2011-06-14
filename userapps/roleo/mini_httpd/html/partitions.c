#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "partitions.h"

int fsckRunning = 0;
int outFsckPresent = 0;
int fdiskRunning = 0;
int outFdiskPresent = 0;

int GetDisks()
{
    int iRet = 0;
    int i, j;
    partition myMounts[256];
    int partNum;
    disk myDisks[256];
    int diskNum;
    
    diskNum = readDisks(&myDisks[0], 256);
    if (diskNum < 0) {
	iRet = -1;
    } else if (diskNum == 0) {
	iRet = 0;
    } else {
	partNum = readPartitions(&myMounts[0], 256);
	
	if (partNum < 0) {
	    iRet = -2;
	} else {
	    readMounts(&myMounts[0], partNum);

	    for (i = 0; i < diskNum; i++) {
		for (j = 0; j < partNum; j++) {
		    if (strncmp(myDisks[i].dev, myMounts[j].dev, strlen(myDisks[i].dev)) == 0) {
			if (myMounts[j].mounted == 1) {
			    myDisks[i].in_use = 1;
			}
		    }
		}
	    
		printf("<tr>");
		printf("<td>%s</td>\n", myDisks[i].dev);
		
		printf("<td align=center><input type='button'");
		printf(" onClick=\"fdiskClick('%s');\" value='Fdisk &amp; Format'", myDisks[i].dev);
		if (myDisks[i].in_use == 1) {
		    printf(" disabled");
		}	    
		printf("></td>\n");

		printf("</tr>");
	    }
	}
    }

    return iRet;
}

int GetPartitionsAndMounts()
{
    int iRet = 0;
    int i;
    partition myMounts[256];
    int partNum;
    
    partNum = readPartitions(&myMounts[0], 256);
    
    if (partNum < 0) {
	iRet = -1;
    } else if (partNum == 0) {
	iRet = 0;
    } else {
	readMounts(&myMounts[0], partNum);

	for (i = 0; i < partNum; i++) {
	    printf("<tr>");
	    printf("<td>%s</td>\n", myMounts[i].dev);
	    
	    if (myMounts[i].mounted == 1) {
		printf("<td>Yes</td>");
	    } else {
		printf("<td>No</td>");
	    }

	    if (myMounts[i].point[0] == '\0') {
		printf("<td>-</td>\n");
	    } else {
		printf("<td>%s</td>\n", myMounts[i].point);
	    }

	    if (myMounts[i].fstype[0] == '\0') {
		printf("<td>-</td>\n");
	    } else {
		printf("<td>%s</td>\n", myMounts[i].fstype);
	    }
	    	    
	    printf("<td align=center><input type='button'");
	    printf(" onClick=\"mountClick('%s');\" value='Mount'", myMounts[i].dev);
	    if (myMounts[i].mounted == 1) {
		printf(" disabled");
	    }	    
	    printf("></td>\n");

	    printf("<td align=center><input type='button'");
	    printf(" onClick=\"umountClick('%s');\" value='Umount'", myMounts[i].dev);
	    if (myMounts[i].mounted == 0) {
		printf(" disabled");
	    }	    
	    printf("></td>\n");

	    printf("<td align=center><input type='button'");
	    printf(" onClick=\"killumountClick('%s');\" value='Kill &amp; Umount'", myMounts[i].dev);
	    if (myMounts[i].mounted == 0) {
		printf(" disabled");
	    }	    
	    printf("></td>\n");
	    
	    printf("<td align=center><input type='button'");
	    printf(" onClick=\"fsckClick('%s');\" value='Fsck'", myMounts[i].dev);
	    if (myMounts[i].mounted == 1) {
		printf(" disabled");
	    }	    
	    printf("></td>\n");

	    printf("</tr>");
	}
    }

    return iRet;
}

int ExecMount(char *device)
{
/*
    char sCommand[256];
    char sDir[256];
    char *pTmp;
    mode_t perms = 0777;

    pTmp = strrchr(device, '/') + 1;
    sprintf(sDir, "%s/%s", MOUNTDIR, pTmp);
    mkdir(MOUNTDIR, perms);
    mkdir(sDir, perms);
    sprintf(sCommand, "%s %s %s > /dev/null 2>&1", MOUNTNTFS3G, device, sDir);
    system(sCommand);
    sprintf(sCommand, "%s %s %s > /dev/null 2>&1", MOUNT, device, sDir);
    system(sCommand);
*/

    int iRet = 0;
    char sCommand[256];
    char sDir[256];
    char *pTmp;
    mode_t perms = 0777;

    pTmp = strrchr(device, '/') + 1;
    sprintf(sDir, "%s/%s", MOUNTDIR, pTmp);
    mkdir(MOUNTDIR, perms);
    mkdir(sDir, perms);
    sprintf(sCommand, "%s %s %s > /dev/null 2>&1", MOUNTNTFS3G, device, sDir);
    iRet = system(sCommand);

    setenv("ACTION", "ADD", 1);
    setenv("DEVPATH", device, 1);
    sprintf(sCommand, "%s block > /dev/null 2>&1", HOTPLUG);
    iRet += system(sCommand);
    
    return iRet;
}

int ExecUmount(char *device, int kill)
{

    int iRet = 0;
    char sCommand[256];
    
    FILE *fs;
    char sMDev[64], sMPoint[64];
    char s1[64], s2[64], s3[64], s4[64];

    // kill all processes related to device
    if (kill == 1) {
	if ((fs=fopen("/proc/mounts","r")) != NULL) {
	    while (fscanf(fs, "%s%s%s%s%s%s", sMDev, sMPoint, s1, s2, s3, s4) != EOF) {
	        //printf ("%s %s\n", sMDev, sMPoint);
    		if (strcmp(sMDev, device) == 0) {
        	    sprintf(sCommand, "/bin/kill `/bin/lsof -t %s` > /dev/null 2>&1", sMPoint);
    		    iRet = system(sCommand);
        	    sleep(1);
		    break;
		}
	    }
    	    fclose(fs);
	} else {
    	    iRet = -1;
	}
    }
    
    // umount via hotplug
    setenv("ACTION", "REMOVE", 1);
    setenv("DEVPATH", device, 1);
    sprintf(sCommand, "%s block > /dev/null 2>&1", HOTPLUG);
    iRet += system(sCommand);

    return iRet;
}

int ExecFsck(char *device)
{
    int iRet = 0;
    char sCommand[256];
    char sEnd[64];
    pid_t pid;
        
    ExecUmount(device, 0);
    
    pid = fork();
    if (pid < 0) { // error
	iRet = -1;
    } else if (pid == 0) { // child
	sprintf(sCommand, "%s -yf %s 2>&1 > %s", FSCK, device, FSCK_OUT);
	system(sCommand);
	sprintf(sEnd, "\n%s\n", OUT_END);
	appendToTextFile(FSCK_OUT, sEnd);
	exit (0);		
    } else { // parent
	
    }
    
    return iRet;
}

int ExecFdisk(char *device)
{
    int iRet = 0;
    char sCommand[256];
    char sEnd[64];
    pid_t pid;
        
    pid = fork();
    if (pid < 0) { // error
	iRet = -1;
    } else if (pid == 0) { // child
	sprintf(sCommand, "%s \";\" | %s %s 2>&1 > %s", ECHO, FDISK, device, FDISK_MKFS_OUT);
	system(sCommand);
	sprintf(sEnd, "\n%s\n", OUT_END);
	appendToTextFile(FDISK_MKFS_OUT, sEnd);
	exit (0);
    } else { // parent
	
    }
    
    return iRet;
}

int ExecFormat(char *device)
{
    int iRet = 0;
    char sCommand[256];
    char sEnd[64];
    pid_t pid;
        
    pid = fork();
    if (pid < 0) { // error
	iRet = -1;
    } else if (pid == 0) { // child
	sprintf(sCommand, "%s %s1 2>&1 > %s", MKFS, device, FDISK_MKFS_OUT);
	system(sCommand);
	sprintf(sEnd, "\n%s\n", OUT_END);
	appendToTextFile(FDISK_MKFS_OUT, sEnd);
	exit (0);
    } else { // parent
	
    }
    
    return iRet;
}

int readDisks(disk *arrayDisk, int diskNum)
{
    int iRet=0;
    FILE *fs;
    char s1[64], s2[64], s3[64];
    int i=0;
    char devName[64];

    memset(arrayDisk, 0, diskNum * sizeof(disk));

    if ((fs=fopen("/proc/partitions","r")) != NULL) {
        while ((fscanf(fs, "%s%s%s%s", s1, s2, s3, devName) != EOF) && (i < diskNum)) {
	    if ((strncmp(devName, "sd", 2) == 0) && 
		((devName[strlen(devName) - 1] < '0') ||
		(devName[strlen(devName) - 1] > '9'))) {

		sprintf(arrayDisk[i].dev, "/dev/%s", devName);
		i++;
	    }
	}
	iRet = i;
	fclose(fs);
    } else {
	iRet = -1;
    }
    
    return iRet;
}

int readPartitions(partition *arrayPartition, int partNum)
{
    int iRet=0;
    FILE *fs;
    char s1[64], s2[64], s3[64];
    int i=0;
    char devName[64];

    memset(arrayPartition, 0, partNum * sizeof(partition));

    if ((fs=fopen("/proc/partitions","r")) != NULL) {
        while ((fscanf(fs, "%s%s%s%s", s1, s2, s3, devName) != EOF) && (i < partNum)) {
	    if ((strncmp(devName, "sd", 2) == 0) && 
		(devName[strlen(devName) - 1] >= '0') &&
		(devName[strlen(devName) - 1] <= '9')) {

		sprintf(arrayPartition[i].dev, "/dev/%s", devName);
		i++;
	    }
	}
	iRet = i;
	fclose(fs);
    } else {
	iRet = -1;
    }
    
    return iRet;
}

int readMounts(partition *arrayPartition, int partNum)
{
    int iRet=0;
    FILE *fs;
    char s1[64], s2[64], s3[64], s4[64];
    int j=0;
    partition rowPart;

    if ((fs=fopen("/proc/mounts","r")) != NULL) {
        while (fscanf(fs, "%s%s%s%s%s%s", rowPart.dev, rowPart.point,
	    rowPart.fstype, s1, s2, s3) != EOF) {
	    
	    for (j = 0; j < partNum; j++) {
		if (strcmp(arrayPartition[j].dev, rowPart.dev) == 0) {
		    arrayPartition[j].mounted = 1;
		    sprintf(arrayPartition[j].point, rowPart.point);
		    sprintf(arrayPartition[j].fstype, rowPart.fstype);
		}
	    }
	}
	fclose(fs);
    } else {
	iRet = -1;
    }

    if ((fs=fopen("/proc/swaps","r")) != NULL) {
        while (fscanf(fs, "%s%s%s%s%s", rowPart.dev, s1, s2, s3, s4) != EOF) {
	    
	    for (j = 0; j < partNum; j++) {
		if (strcmp(arrayPartition[j].dev, rowPart.dev) == 0) {
		    arrayPartition[j].mounted = 1;
//		    sprintf(arrayPartition[j].point, "");
		    arrayPartition[j].point[0] = '\0';
		    sprintf(arrayPartition[j].fstype, "swap");
		}
	    }
	}
	fclose(fs);
    } else {
	iRet = -2;
    }
		    	
    return iRet;
}

void GetFsckVar()
{
    char sRow[1024];
    FILE *fs = NULL;
        
    if (fileExists(FSCK_OUT) == 0) {

	if ((fs=fopen(FSCK_OUT, "r")) != NULL) {
	    fsckRunning = 1;
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {
		if (strncmp(OUT_END, sRow, strlen(OUT_END)) == 0) {
		    fsckRunning = 0;
		}
	    }
	    fclose(fs);
	} else {
	    fsckRunning = 1;
	}
	outFsckPresent = 1;
    } else {
	fsckRunning = 0;
	outFsckPresent = 0;
    }

    return;
}

void GetFsckRefresh(int secs)
{
    GetFsckVar();
    
    if (fsckRunning == 1) {
	printf("<meta http-equiv=\"refresh\" content=\"%d\">\n", secs);
    }
    return;
}

void GetFsckStatus(char *device)
{
    GetFsckVar();
    
    if ((fsckRunning == 0) && (outFsckPresent == 0)) {
	printf("<p>Press <b>Start</b> to start file system check on <b>%s</b></p>\n", device);
	printf("<p><form><input type='button'");
	printf(" onClick=\"startFsckClick('%s');\" value='Start'></form></p><br>\n", device);
    } else if ((fsckRunning == 0) && (outFsckPresent == 1)) {
	printf("<p>Press <b>Start</b> to start file system check on <b>%s</b></p>\n", device);
	printf("<p><form><input type='button'");
	printf(" onClick=\"startFsckClick('%s');\" value='Start'></form></p><br>\n", device);
	printf("<p>This is the log of the last run:</p>\n");
    } else if (fsckRunning == 1) {
	printf("<p>This is the log of the current run:</p>\n");
    }

    return;
}

void GetFsckOut(char *device)
{
    char sRow[1024];
    FILE *fs = NULL;

        
    if (outFsckPresent == 1) {
	if ((fs=fopen(FSCK_OUT, "r")) != NULL) {
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {
		printf("%s", sRow);
	    }
	    fclose(fs);
	}
    }
    return;
}

void GetFdiskVar()
{
    char sRow[1024];
    FILE *fs = NULL;
        
    if (fileExists(FDISK_MKFS_OUT) == 0) {

	if ((fs=fopen(FDISK_MKFS_OUT, "r")) != NULL) {
	    fdiskRunning = 1;
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {
		if (strncmp(OUT_END, sRow, strlen(OUT_END)) == 0) {
		    fdiskRunning = 0;
		}
	    }
	    fclose(fs);
	} else {
	    fdiskRunning = 1;
	}
	outFdiskPresent = 1;
    } else {
	fdiskRunning = 0;
	outFdiskPresent = 0;
    }

    return;
}

void GetFdiskRefresh(int secs)
{
    if (fdiskRunning == 1) {
	printf("<meta http-equiv=\"refresh\" content=\"%d\">\n", secs);
    }
    return;
}

void GetFdiskStatus(char *device)
{
    if ((fdiskRunning == 0) && (outFdiskPresent == 0)) {
	printf("<p>Press the following buttons to start drive partition or format on <b>%s</b></p>\n", device);
	printf("<p><form><input type='button'");
	printf(" onClick=\"startFdiskClick('%s');\" value='Fdisk'></form></p><br>\n", device);
	printf("<p><form><input type='button'");
	printf(" onClick=\"startFormatClick('%s');\" value='Format'></form></p><br>\n", device);
    } else if ((fdiskRunning == 0) && (outFdiskPresent == 1)) {
	printf("<p>Press the following buttons to start drive partition or format on <b>%s</b></p>\n", device);
	printf("<p><form><input type='button'");
	printf(" onClick=\"startFdiskClick('%s');\" value='Fdisk'></form></p><br>\n", device);
	printf("<p><form><input type='button'");
	printf(" onClick=\"startFormatClick('%s');\" value='Format'></form></p><br>\n", device);
	printf("<p>This is the log of the last run:</p>\n");
    } else if (fdiskRunning == 1) {
	printf("<p>This is the log of the current run:</p>\n");
    }

    return;
}

void GetFdiskOut(char *device)
{
    char sRow[1024];
    FILE *fs = NULL;

    if (outFdiskPresent == 1) {
	if ((fs=fopen(FDISK_MKFS_OUT, "r")) != NULL) {
    	    while (fgets(sRow, sizeof(sRow), fs) != NULL) {
		printf("%s", sRow);
	    }
	    fclose(fs);
	}
    }
    return;
}

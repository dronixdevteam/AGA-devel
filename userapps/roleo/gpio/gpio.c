#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>  /* ioctl */
#include "board.h"

static int boardIoctl(int boardFd, int board_ioctl, BOARD_IOCTL_ACTION action, char *string, int strLen, int offset)
{
    BOARD_IOCTL_PARMS IoctlParms;
    
    IoctlParms.string = string;
    IoctlParms.strLen = strLen;
    IoctlParms.offset = offset;
    IoctlParms.action = action;

    ioctl(boardFd, board_ioctl, &IoctlParms);

    return (IoctlParms.result);
}

static void sysGpioCtrl(int gpioNum, int gpioState)
{
    int boardFd;

    if ((boardFd = open("/dev/brcmboard", O_RDWR)) == -1) 
        printf("Unable to open device /dev/brcmboard.\n");

    boardIoctl(boardFd, BOARD_IOCTL_GPIO_CTRL, 0, "", gpioNum, gpioState);
    close(boardFd);
}

void main(int argc, char *argv[])
{
    if (argc != 3) {
	exit (-1);
    }

    sysGpioCtrl(atoi(argv[1]), atoi(argv[2]));
    return;
}

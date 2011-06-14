/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA02111-1307USA
*
* Feedback, Bugs...  blogic@openwrt.org 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "gpio_api.h"
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

//******************************************************************************
// Configure GPIO bit according to the passed values
//******************************************************************************
static void sysGpioCtrl (int gpioNum, int gpioState)
{
    int boardFd;
    
    if ((boardFd = open("/dev/brcmboard", O_RDWR)) == -1)
	printf("Unable to open device /dev/brcmboard.\n");
	
    boardIoctl(boardFd, BOARD_IOCTL_GPIO_CTRL, 0, "", gpioNum, gpioState);
    close(boardFd);
}

void sysSetGpioBit (int gpioNum, int gpioState)
{
    sysGpioCtrl (gpioNum, gpioState);
}

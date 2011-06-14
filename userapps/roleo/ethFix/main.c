/*
 *
 * AUTHOR:   Stefano Viola (aka) Esteban Sannin
 * CONTACT:  stefanoviola[at]sannioglug[dot]org
 * HOME:     http://esteban.homelinux.org   
 *
 *      Licenze GLPv3
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      3 of the License, or (at your option) any later version.
 *
 */

#include <stdio.h>
#include "include/data-traffic.h"
#include <unistd.h>

int main(int argc, char *argv[]){
	int rate;
	//printf("%d\n",argc);
	if (argc == 2){
		rate = atoi(argv[1]);
		if(rate == 0){
			rate = 1200;
			//printf("Start with default rate: %d\n",rate);
		}
	} else {
		rate = 1200;
		//printf("Start with default rate: %d\n",rate);
	}
	int pid;
	if(fork()) return 0;
	chdir("/");
	setsid();
	umask(0);
	pid=fork();
	if(pid){
		printf("Ethernet fix started with pid %d\n",pid);
		printf("Blinking led to data rate: %d\n",rate);
		exit(1);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	data_byte_rate(rate);
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "board_api.h"

#define RSISTART 0xBF7F0000
#define RSILEN 32768

void usage(char *strname)
{
    printf("Usage:\n");
    printf("%s rsi\n", strname);
    printf("\t\tto dump entire rsi area\n");
    printf("%s <StartAddress> <Length>\n", strname);
    printf("\t\tto dump Length bytes from Start Address\n");
}

void main(int argc, char *argv[])
{
    if (argc == 2) {
	if (strcasecmp(argv[1], "rsi") == 0) {
	    sysDumpAddr((char *) RSISTART, RSILEN);
	}
    } else if (argc == 3) {
	unsigned long ulTmp = strtoul(argv[1], NULL, 16);
	sysDumpAddr((char *) ulTmp, atoi(argv[2]));
    } else {
	usage(argv[0]);
    }
}

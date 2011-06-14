#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../shared/rsi_api.h"

void usage(char *strname)
{
    printf("Usage: %s tag1 tag2 attribute\n", strname);
}

int main(int argc, char *argv[])
{
    int iRet = 0;

    if (argc != 4) {
	usage(argv[0]);
	iRet = -1;
    } else {
	// Reading entry
	strcpy(str_tag1_name, argv[1]);
	sprintf(str_tag2_name, argv[2]);
	strcpy(str_attribute_name, argv[3]);
	read_attribute();
	if (find_status.value_found == 1) {
    	    printf("%s\n", str_attribute_value);
	} else {
    	    printf("Value not found\n");
	}
    }
    
    return iRet;
}


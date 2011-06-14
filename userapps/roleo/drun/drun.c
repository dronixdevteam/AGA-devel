#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

void usage(char *strname)
{
    printf("Usage: %s command n\n", strname);
    printf("\tcommand\tscript to execute\n");
    printf("\tn\tdelay (seconds)\n");
}

int main(int argc, char **argv)
{
    int isec;
    struct stat s;
    
    if (argc != 3) {
	usage(argv[0]);
	return -1;
    }

    if (stat(argv[1], &s) != 0) {
	printf("Error: file %s doesn't exist\n", argv[1]);
	usage(argv[0]);
        return -3;
    }

    if ((argv[2][0] < '0') || (argv[2][0] > '9')) {
	printf("Error: option %s is not numeric\n", argv[2]);
	usage(argv[0]);
	return -2;
    }
    
    isec=atoi(argv[2]);
    
    if (fork())
	exit(0);  /* Exit from parent process */
    setsid();

    sleep(isec);
    system(argv[1]);

    return 0;
}

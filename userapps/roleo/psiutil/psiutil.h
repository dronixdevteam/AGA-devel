#include <stdlib.h>
#include <string.h>
#include <psixml.h>
#include <sys/stat.h>

void usage(char *strname);
int main(int argc, char *argv[]);
void clearcfg();
int dumpcfg();
int loadcfg(char *strfile);

#include <stdlib.h>
#include <string.h>
#include <psixml.h>
#include <sys/stat.h>

#define XML_RSI_START_TAG      "<rsitree>"
#define XML_RSI_END_TAG        "</rsitree>"
#define MAX_BLANK_RSI_SIZE 64

void usage(char *strname);
int main(int argc, char *argv[]);
void clearcfg();
int dumpcfg();
int loadcfg(char *strfile);
int check_rsi();

// Vedi www.w3.org/CGI/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

#define LF 10
#define CR 13

void getword(char *word, char *line, char stop) {
    int x = 0,y;

    for(x=0;((line[x]) && (line[x] != stop));x++)
        word[x] = line[x];

    word[x] = '\0';
    if(line[x]) ++x;
    y=0;

    while((line[y++] = line[x++]));
}

char *makeword(char *line, char stop) {
    int x = 0,y;
    char *word = (char *) malloc(sizeof(char) * (strlen(line) + 1));

    for(x=0;((line[x]) && (line[x] != stop));x++)
        word[x] = line[x];

    word[x] = '\0';
    if(line[x]) ++x;
    y=0;

    while((line[y++] = line[x++]));
    return word;
}

char *fmakeword(FILE *f, char stop, int *cl) {
    int wsize;
    char *word;
    int ll;

    wsize = 102400;
    ll=0;
    word = (char *) malloc(sizeof(char) * (wsize + 1));

    while(1) {
        word[ll] = (char)fgetc(f);
        if(ll==wsize) {
            word[ll+1] = '\0';
            wsize+=102400;
            word = (char *)realloc(word,sizeof(char)*(wsize+1));
        }
        --(*cl);
        if((word[ll] == stop) || (feof(f)) || (!(*cl))) {
            if(word[ll] != stop) ll++;
            word[ll] = '\0';
            return word;
        }
        ++ll;
    }
}

char x2c(char *what) {
    register char digit;

    digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
    digit *= 16;
    digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
    return(digit);
}

void unescape_url(char *url) {
    register int x,y;

    for(x=0,y=0;url[y];++x,++y) {
        if((url[x] = url[y]) == '%') {
            url[x] = x2c(&url[y+1]);
            y+=2;
        }
    }
    url[x] = '\0';
}

void plustospace(char *str) {
    register int x;

    for(x=0;str[x];x++) if(str[x] == '+') str[x] = ' ';
}

int rind(char *s, char c) {
    register int x;
    for(x=strlen(s) - 1;x != -1; x--)
        if(s[x] == c) return x;
    return -1;
}

int getline(char *s, int n, FILE *f) {
    register int i=0;

    while(1) {
        s[i] = (char)fgetc(f);

        if(s[i] == CR)
            s[i] = fgetc(f);

        if((s[i] == 0x4) || (s[i] == LF) || (i == (n-1))) {
            s[i] = '\0';
            return (feof(f) ? 1 : 0);
        }
        ++i;
    }
}

void send_fd(FILE *f, FILE *fd)
{
//    int num_chars=0;
    char c;

    while (1) {
        c = fgetc(f);
        if(feof(f))
            return;
        fputc(c,fd);
    }
}

int fileExists(char *filename)
{
    int iRet;
    
    if (access(filename, F_OK) == 0) {
	// file exists
	iRet=0;
    } else {
	// file doesn't exist
	iRet=1;
    }
    return iRet;
}

int fileCopy(char *sourceFile, char *destFile)
{
    FILE *inFile;
    FILE *outFile;
    int Byte = 1;
    int iRet = 0;

    inFile = fopen(sourceFile, "rb");
    if(inFile==NULL) {
	iRet = -1;
    } else {
	outFile = fopen(destFile, "wb");
	if(outFile==NULL) {
	    iRet = -2;
	} else {
	    while(1) {
		if((Byte=fgetc(inFile)) != EOF) {
		    fputc(Byte,outFile);
		} else {
		    break;
		}
	    }
	    fclose(outFile);
	}
	fclose(inFile);
    }
    
    return iRet;
}

char *trim(char *input)
{
    int i;
    
    for (i=strlen(input)-1; i>=0; i--) {
        if ((input[i] != ' ') && (input[i] != '\t')) {
            break;
        }
    }
    input[i+1] = '\0';

    for (i=0; i<strlen(input); i++) {
        if ((input[i] != ' ') && (input[i] != '\t')) {
            break;
        }
    }
    return (input + i);
}

int appendToTextFile(char *strFilename, char *strPrint) {
    FILE *ftextconf = NULL;
    int iRet=0;

    ftextconf = fopen(strFilename, "a");

    if ( ftextconf == NULL ) {
        iRet=-1;
    } else {
        fprintf(ftextconf, strPrint);
        fclose(ftextconf);
        iRet=0;
    }

    return iRet;
}

// return 1 if access is granted, 0 if access is not granted
int verifyWANAccess(int tcpport)
{
    FILE *fp;
    char line[256];
    char *token;
    int iRet = 0;
    int ruleFound = 0;
    char sCommand[256];
    char sTmp[26];
    
    sprintf(sCommand, "%s -L INPUT -n 2>/dev/null", IPTABLES);
    fp = popen(sCommand, "r");   
    if (fp != NULL) {
	while (fgets(line, sizeof(line), fp)) {
	    token=strtok(line, " \t");
	    if ((token != NULL) && (strcmp("ACCEPT", token) == 0)) {
		token=strtok(NULL, " \t");
		if ((token != NULL) && (strcmp("tcp", token) == 0)) {
		    token=strtok(NULL, " \t");
		    if ((token != NULL) && (strcmp("--", token) == 0)) {
			token=strtok(NULL, " \t");
			if ((token != NULL) && (strcmp("0.0.0.0/0", token) == 0)) {
			    token=strtok(NULL, " \t");
			    if ((token != NULL) && (strcmp("0.0.0.0/0", token) == 0)) {
				token=strtok(NULL, " \t");
				if ((token != NULL) && (strcmp("tcp", token) == 0)) {
				    token=strtok(NULL, " \t");
				    sprintf(sTmp, "dpt:%d", tcpport);
				    if ((token != NULL) && (strcmp(sTmp, token) == 0)) {
					ruleFound = 1;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
	pclose(fp);
    } else {
	iRet = -1;
    }
    
    if (ruleFound == 1) {
	iRet = 1;
    }
    
    return iRet;
}


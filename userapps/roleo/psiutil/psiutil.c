#include <psiutil.h>

void usage(char *strname)
{
    printf("Usage: %s cmd\n", strname);
    printf("\tcmd:\tclear to restore factory default\n");
    printf("\t\tdump to dump psitree\n");
    printf("\t\tload <filename> to load cfg file\n");
}

int main(int argc, char *argv[])
{
    int iRet=0;
    
    if ((argc < 2) || (argc > 3)) {
        usage(argv[0]);
        return -1;
    }
    if ((argc == 3) && (strcmp("load", argv[1]) != 0)) {
        usage(argv[0]);
        return -2;
    }
    
    if (strcmp("clear", argv[1])==0) {
	clearcfg();
	printf("psitree restored to factory default\n");
    } else if (strcmp("dump", argv[1])==0) {
        if (dumpcfg() != 0) {
	    printf("Error dumping psitree\n");
	    iRet = -3;
	}	    
    } else if (strcmp("load", argv[1])==0) {
        if (loadcfg(argv[2]) == 0) {
	    printf("Configuration file loaded, the system must be rebooted\n");
	} else {
	    printf("Error dumping psitree\n");
	    iRet = -4;
	}	    
    } else {
        usage(argv[0]);
        iRet = -5;
    }

    return iRet;
}

void clearcfg()
{
    BcmDb_restoreDefault();
}

int dumpcfg()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int psiSize = 0;
    char *pc = NULL;
    psiSize = sysGetPsiSize();
    if ((strXmlBuf = malloc(psiSize)) == NULL) {
        printf("Failed to allocate %d bytes of memory.\n", psiSize);
        return -1;
    }
    sysPersistentGet(strXmlBuf, psiSize, 0);

    // if <psitree> cannot be found then return
    if (memcmp(strXmlBuf, XML_PSI_START_TAG, strlen(XML_PSI_START_TAG)) == 0) {
	// determine data length
        pc = strstr(strXmlBuf, XML_PSI_END_TAG);
        if (pc != NULL)
        xmlCfgLen = pc - strXmlBuf + strlen(XML_PSI_END_TAG);
	strXmlBuf[xmlCfgLen]='\0';
    } else  {
        printf("Invalid configuration data or psitree not found.\n");
	free(strXmlBuf);
        return -1;
    }

    printf("%s\n", strXmlBuf);
    free(strXmlBuf);
    return 0;
}

int loadcfg(char *strfile)
{
    int iRet;
    struct stat s;
    FILE *pFile;
    char *buffer;
    
    if (stat(strfile, &s) != 0) {
        printf("Error: file %s doesn't exist\n", strfile);
	return -1;
    }
    pFile = fopen(strfile, "r");
    if (pFile == NULL) {			    
        printf("Error opening file %s\n", strfile);
	return -2;
    }
    
    buffer = (char *) malloc(s.st_size * sizeof(char));
    iRet = fread(buffer,1 , s.st_size, pFile);
    if (iRet != s.st_size) {
        printf("Error reading file %s\n", strfile);
	free(buffer);
	return -3;
    }
    
    fclose(pFile);
    sysPersistentSet(buffer, s.st_size, 0);
    free(buffer);
    return 0;
}

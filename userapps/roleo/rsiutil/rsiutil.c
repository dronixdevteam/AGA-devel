#include "../shared/rsi_api.h"
#include "rsiutil.h"

void usage(char *strname)
{
    printf("Usage: %s cmd\n", strname);
    printf("\tcmd:\tclear to restore factory default\n");
    printf("\t\tdump to dump rsi\n");
    printf("\t\tload <filename> to load cfg file\n");
    printf("\t\tcheck to verify syntax\n");
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
	printf("rsi restored to factory default\n");
    } else if (strcmp("dump", argv[1])==0) {
        if (dumpcfg() != 0) {
	    printf("Error dumping rsi\n");
	    iRet = -3;
	}	    
    } else if (strcmp("load", argv[1])==0) {
        if (loadcfg(argv[2]) == 0) {
	    printf("Configuration file successfully loaded\n");
	} else {
	    printf("Error loadig rsi\n");
	    iRet = -4;
	}
    } else if (strcmp("check", argv[1])==0) {
        if (check_rsi() == 0) {
            printf("rsitree check done\n");
            iRet = 0;
        } else {
            printf("Error checking rsitree\n");
            iRet = -5;
        }
    } else {
        usage(argv[0]);
        iRet = -6;
    }

    return iRet;
}

void clearcfg()
{
    char *strXmlBuf = NULL;
    int rsiSize = 0;
    
    rsiSize = sysGetRsiSize();
    if ((strXmlBuf = malloc(rsiSize)) == NULL) {
        printf("Failed to allocate %d bytes of memory.\n", rsiSize);
    }
    memset(strXmlBuf, 0xFF, rsiSize);

    sprintf(strXmlBuf, "<rsitree>\n");
    sprintf(strXmlBuf, "%s<samba>\n</samba>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<ftpd>\n</ftpd>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<udhcpd>\n</udhcpd>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<adslctl>\n</adslctl>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<wlan>\n</wlan>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<printer>\n</printer>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<webcam>\n</webcam>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<wol>\n</wol>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<profile>\n</profile>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s<regbutton>\n</regbutton>\n", strXmlBuf);
    sprintf(strXmlBuf, "%s</rsitree>\n", strXmlBuf);

    sysRsiSet(strXmlBuf, rsiSize, 0);
    free(strXmlBuf);
}

int dumpcfg()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;
    int rsiSize = 0;
    char *pc = NULL;
    
    rsiSize = sysGetRsiSize();
    if ((strXmlBuf = malloc(rsiSize)) == NULL) {
        printf("Failed to allocate %d bytes of memory.\n", rsiSize);
        return -1;
    }
    memset(strXmlBuf, 0xFF, rsiSize);
    sysRsiGet(strXmlBuf, rsiSize, 0);

    // if <rsitree> cannot be found then return
    if (memcmp(strXmlBuf, XML_RSI_START_TAG, strlen(XML_RSI_START_TAG)) == 0) {
	// determine data length
        pc = strstr(strXmlBuf, XML_RSI_END_TAG);
        if (pc != NULL)
    	    xmlCfgLen = pc - strXmlBuf + strlen(XML_RSI_END_TAG);
	strXmlBuf[xmlCfgLen]='\0';
    } else  {
        printf("Invalid configuration data or rsitree not found.\n");
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
    sysRsiSet(buffer, s.st_size, 0);
    free(buffer);
    return 0;
}

int check_rsi()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int rsiSize = 0;
    char *pc = NULL;
    char *blank_rsi;
    
    int rsitreeModified = 0;
    
    rsiSize = sysGetRsiSize();
    if ((strXmlBuf = malloc(rsiSize + 1)) == NULL)
    {
        printf("Failed to allocate %d bytes of memory.\n", rsiSize + 1);
        return -1;
    }
    memset(strXmlBuf, 0xFF, rsiSize + 1);
    sysRsiGet(strXmlBuf, rsiSize, 0);
    strXmlBuf[rsiSize] = '\0';

    // if <rsitree> cannot be found then fix and return
    if (memcmp(strXmlBuf, XML_RSI_START_TAG, strlen(XML_RSI_START_TAG)) == 0) {
	// determine data length
	pc = strstr(strXmlBuf, XML_RSI_END_TAG);
	if (pc != NULL)
	    xmlCfgLen = pc - strXmlBuf + strlen(XML_RSI_END_TAG) + 1;
        strXmlBuf[xmlCfgLen - 1] = '\0';

	printf("rsitree found\n");

    } else  {
        if ((blank_rsi = malloc(rsiSize)) == NULL)
	{
    	    printf("Failed to allocate %d bytes of memory.\n", rsiSize);
	    free(strXmlBuf);
    	    return -1;
	}
    
	memset(blank_rsi, 0xFF, rsiSize);
	sprintf(blank_rsi, "<rsitree>\n");
	sprintf(blank_rsi, "%s<samba>\n</samba>\n", blank_rsi);
	sprintf(strXmlBuf, "%s<ftpd>\n</ftpd>\n", strXmlBuf);
	sprintf(blank_rsi, "%s<udhcpd>\n</udhcpd>\n", blank_rsi);
	sprintf(blank_rsi, "%s<adslctl>\n</adslctl>\n", blank_rsi);
	sprintf(blank_rsi, "%s<wlan>\n</wlan>\n", blank_rsi);
	sprintf(blank_rsi, "%s<printer>\n</printer>\n", blank_rsi);
	sprintf(blank_rsi, "%s<webcam>\n</webcam>\n", blank_rsi);
	sprintf(blank_rsi, "%s<wol>\n</wol>\n", blank_rsi);
	sprintf(blank_rsi, "%s<profile>\n</profile>\n", blank_rsi);
	sprintf(blank_rsi, "%s<regbutton>\n</regbutton>\n", blank_rsi);
	sprintf(blank_rsi, "%s</rsitree>\n", blank_rsi);
        sysRsiSet(blank_rsi, rsiSize, 0);
	free(blank_rsi);
	free(strXmlBuf);
	
	printf("Unable to find rsitree, default restored\n");
	
	return 0;
    }

    if ((xmlCfgLen + MAX_BLANK_RSI_SIZE) > rsiSize) {
	free(strXmlBuf);
	return -3;
    }

    char *ps, *pe;
    char *newRsi;
    long lTmpSize;
    
    newRsi = (char *) malloc(rsiSize);
    memset(newRsi, 0xFF, rsiSize);

    sprintf(newRsi, "<rsitree>\n");
    
    read_section_bounds(strXmlBuf, "samba", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<samba>\n</samba>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "ftpd", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<ftpd>\n</ftpd>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "udhcpd", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<udhcpd>\n</udhcpd>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "adslctl", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<adslctl>\n</adslctl>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "wlan", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<wlan>\n</wlan>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "printer", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<printer>\n</printer>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "webcam", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<webcam>\n</webcam>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "wol", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<wol>\n</wol>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "profile", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<profile>\n</profile>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    read_section_bounds(strXmlBuf, "regbutton", &ps, &pe);
    if ((ps == NULL) || (pe == NULL)) {
	sprintf(newRsi, "%s<regbutton>\n</regbutton>\n", newRsi);
	rsitreeModified = 1;
    } else {
	lTmpSize = strlen(newRsi);
	memcpy(&newRsi[lTmpSize], ps, pe - ps + 1);
	newRsi[lTmpSize + pe - ps + 1] = '\n';
	newRsi[lTmpSize + pe - ps + 2] = '\0';
    }

    sprintf(newRsi, "%s</rsitree>\n", newRsi);
    
    if (rsitreeModified == 1) {
	printf("rsitree modified\n");
	sysRsiSet(newRsi, rsiSize, 0);
    } else {
	printf("rsitree is ok\n");
    }
    
    free(newRsi);
    free(strXmlBuf);

    return 0;
}


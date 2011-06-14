#include <stdlib.h>
#include <string.h>
#include <psixml.h>
#include <errno.h>
#include "rsiconfadsl.h"
#include "../shared/rsi_api.h"

int getADSLpsi(char *pADSL)
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int psiSize = 0;
    char *pc = NULL;
    
    psiSize = sysGetPsiSize();
    if ((strXmlBuf = malloc(psiSize + 1)) == NULL)
    {
        //printf("Failed to allocate %d bytes of memory.\n", psiSize + 1);
        return -1;
    }
    memset(strXmlBuf, 0xFF, psiSize + 1);
    sysPersistentGet(strXmlBuf, psiSize, 0);
    strXmlBuf[psiSize] = '\0';

    // if <psitree> cannot be found then fix and return
    if (memcmp(strXmlBuf, XML_PSI_START_TAG, strlen(XML_PSI_START_TAG)) == 0) {
	// determine data length
	pc = strstr(strXmlBuf, XML_PSI_END_TAG);
	if (pc != NULL)
	    xmlCfgLen = pc - strXmlBuf + strlen(XML_PSI_END_TAG) + 1;
        strXmlBuf[xmlCfgLen - 1] = '\0';

//	printf("psitree found\n");

    } else  {
	free(strXmlBuf);
//	printf("Unable to find psitree\n");
	
	return -1;
    }

    char *ps, *pe;
    
    ps = strstr(strXmlBuf, "<ADSL>");
    pe = strstr(strXmlBuf, "</ADSL>") + strlen("ADSL") + 2;

    if ((ps == NULL) || (pe == NULL)) {
	free(strXmlBuf);
//	printf("Unable to find psitree\n");
	
	return -2;
    } else {
	snprintf(pADSL, pe - ps + 1, "%s", ps);
    }
    
    free(strXmlBuf);

    return 0;
}

int findValue(char *string, char *name, char *value) {
    char copyofstring[1024];
    char strName[64];
    char *token1 = NULL, *token2 = NULL, *ps = NULL, *pe = NULL;
    int iRet = -1;
    
    strcpy(copyofstring, string);
    sprintf(strName, "%s=", name);
    token1 = strtok(copyofstring, " /");
    while (token1 != NULL) {
	token1 = strtok(NULL, " /");
	if (token1[0] == '>') return iRet;
	
	if (strncasecmp(strName, token1, strlen(strName)) == 0) {
	    token2 = strchr(token1, '=');
	    if (token2 != NULL) {
		token2++;
		
		for (ps = token2, pe = token2 + strlen(token2); ps < pe; ps++) {
		    if ((*ps == ' ') || (*ps == '\"'))
			token2++;
		    else break;
		}
		for (ps = token2, pe = token2 + strlen(token2)-1; pe >= ps; pe--) {
		    if ((*pe == ' ') || (*pe == '\"'))
			*pe = '\0';
		    else break;
		}
		sprintf(value, "%s", token2);
		iRet = 0;
		break;
	    }
	}
    }
    
    return iRet;
}

int getADSLsnr(int *snr)
{
    int iRet = 0;
    char strTmp[256];
    
    strTmp[0] = '\0';
    
    // Reading adslctl configuration
    strcpy(str_tag1_name, "adslctl");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strTmp, "%s", str_attribute_value);
	if (strcasecmp("enable", strTmp) != 0) {
    	    return -1;
	}
	
	strcpy(str_attribute_name, "snr");
	read_attribute();
	if (find_status.value_found == 1) {
    	    sprintf(strTmp, "%s", str_attribute_value);
    	    *snr = strtol(strTmp, NULL, 10);
    	    if ((errno == EINVAL) || (errno == ERANGE)) {
		iRet = -2;
    	    }
	}
	
    } else {
	iRet = -3;
    }
    
    return iRet;
}

int getADSLtrellis(int *trellis)
{
    int iRet = 0;
    char strTmp[256];
    
    strTmp[0] = '\0';
    
    // Reading adslctl configuration
    strcpy(str_tag1_name, "adslctl");
    sprintf(str_tag2_name, "global");
    strcpy(str_attribute_name, "state");
    read_attribute();
    if (find_status.value_found == 1) {
	sprintf(strTmp, "%s", str_attribute_value);
	if (strcasecmp("enable", strTmp) != 0) {
    	    return -1;
	}

	strcpy(str_attribute_name, "trellis");
	read_attribute();
	if (find_status.value_found == 1) {
    	    sprintf(strTmp, "%s", str_attribute_value);
	    if (strcasecmp("on", strTmp) == 0) {
		*trellis = 1;
    	    } else {
		*trellis = 0;
	    }
	}
    
    } else {
	iRet = -2;
    }
    
    return iRet;
}

int configure_adslctl(int force)
{
    char strADSLpsi[1024];
    char strValue[64];
    int iRes;
    char strCommandLine[1024];
    char strTmp[256];
    int iTmp = 0;
    int iES = 0;
    
    getADSLpsi(strADSLpsi);
    
    sprintf(strCommandLine, "/bin/adslctl configure");
    strTmp[0] = '\0';
    
//    printf("%s\n", strADSLpsi);
    iRes = findValue(strADSLpsi, "G.Dmt", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%sd", strTmp);

    iRes = findValue(strADSLpsi, "G.Lite", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%sl", strTmp);

    iRes = findValue(strADSLpsi, "T1.413", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%st", strTmp);

    iRes = findValue(strADSLpsi, "ADSL2", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%s2", strTmp);

    iRes = findValue(strADSLpsi, "AnnexL", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%se", strTmp);

    iRes = findValue(strADSLpsi, "ADSL2plus", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%sp", strTmp);

    iRes = findValue(strADSLpsi, "Annexm", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "%sm", strTmp);

    if (strTmp[0] != '\0') {
	sprintf(strCommandLine, "%s --mod %s", strCommandLine, strTmp);
    }

    strTmp[0] = '\0';
    
    // BITSWAP
    iRes = findValue(strADSLpsi, "bitswap", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "on");
    else
	sprintf(strTmp, "off");

    sprintf(strCommandLine, "%s --bitswap %s", strCommandLine, strTmp);
    
    // SRA
    iRes = findValue(strADSLpsi, "SRA", strValue);
    if ((iRes == 0) && (strcasecmp("enable", strValue) == 0))
	sprintf(strTmp, "on");
    else
	sprintf(strTmp, "off");

    sprintf(strCommandLine, "%s --sra %s", strCommandLine, strTmp);
    
    // PAIR
    iRes = findValue(strADSLpsi, "pair", strValue);
    if ((iRes == 0) && (strcasecmp("outer", strValue) == 0))
	sprintf(strTmp, "o");
    else
	sprintf(strTmp, "i");

    sprintf(strCommandLine, "%s --lpair %s", strCommandLine, strTmp);

    // SNR
    strTmp[0] = '\0';
    if (getADSLsnr(&iTmp) == 0) {
	iES = 1;
	sprintf(strCommandLine, "%s --snr %d", strCommandLine, iTmp);
    }
    
    // TRELLIS    
    strTmp[0] = '\0';
    if (getADSLtrellis(&iTmp) == 0) {
	iES = 1;
	if (iTmp == 1) {
	    sprintf(strTmp, "on");
	} else {
	    sprintf(strTmp, "off");
	}
	sprintf(strCommandLine, "%s --trellis %s", strCommandLine, strTmp);
    }

    if ((iES == 1) || (force == 1)) {
	printf("Running adslctl command:\n%s\n", strCommandLine);
        system(strCommandLine);
    }
    
    return 0;
}

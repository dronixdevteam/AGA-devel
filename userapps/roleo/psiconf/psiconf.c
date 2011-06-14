#include "psiconf.h"

void usage(char *strname)
{
    printf("Usage: %s cmd\n", strname);
    printf("\tcmd:\tmount to configure file system mounts\n");
    printf("\t\tbftpd to configure anonymous profile for bftpd\n");
    printf("\t\tsamba to configure smb.conf\n");
}
	    
int main(int argc, char*argv[])
{
    int iRet=0;
    
    if (argc != 2) {
	usage(argv[0]);
	return -1;
    }
    
    if (strcmp("samba", argv[1])==0) {
	if (configure_samba() == 0) {
	    printf("samba configuration done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -2;
	}
    } else if (strcmp("bftpd", argv[1])==0) {
	if (configure_bftpd() == 0) {
	    printf("bftpd configuration done\n");
	    iRet = 0;
	} else {
	    printf("Error creating ftp user\n");
	    iRet = -3;
	}
    } else if (strcmp("mount", argv[1])==0) {
	if (configure_mount() == 0) {
	    printf("mount operation done\n");
	    iRet = 0;
	} else {
	    printf("Missing parameters\n");
	    iRet = -4;
	}
    } else {
	usage(argv[0]);
	iRet = -5;
    }
    
    return iRet;
}

int configure_mount()
{
    int iRet=0;
    char strMount[MAX_MOUNT_CMD_SIZE];
    
    int boo;
    for (boo =1; boo > 0; boo++) {
        // Reading mount parameters: device, fstype, path
        // Optional parameters
        sprintf(strMount, "%s -t", MOUNT);
	strcpy(str_tag1_name, "mount");
	sprintf(str_tag2_name, "entry%d", boo);
        strcpy(str_attribute_name, "fstype");
        read_attribute();
	if (find_status.value_found == 1) {
	    sprintf(strMount, "%s %s", strMount, str_attribute_value);

	    strcpy(str_attribute_name, "device");
    	    read_attribute();
	    if (find_status.value_found == 1) {
	        sprintf(strMount, "%s %s", strMount, str_attribute_value);

		strcpy(str_attribute_name, "path");
    		read_attribute();
		if (find_status.value_found == 1) {
	    	    sprintf(strMount, "%s %s", strMount, str_attribute_value);
    
		    printf("%s\n", strMount);
		    system(strMount);
		} else {
		    boo=-1;
		}
	    } else {
	        boo=-1;
	    }
	} else {
	    boo=-1;
	}
    }
    return iRet;
}

int configure_bftpd()
{
    int iRet=0;
    char strUpdatePasswd[MAX_PWD_UPDATE_SIZE];
    
    strUpdatePasswd[0]='\0';

    strcpy(str_tag1_name, "bftpd");
    
    // Reading anonymous parameters: home
    // Mandatory parameters
    strcpy(str_tag2_name, "anonymous");
    strcpy(str_attribute_name, "home");
    read_attribute();
    if (find_status.value_found == 1) {
    //    printf("%s\n", str_attribute_value);
	sprintf(strUpdatePasswd, "ftp::500:65534:FTP user:%s:/bin/false\n", str_attribute_value);
	if (appendToTextFile(ETCPASSWD, strUpdatePasswd) == 0) {
	    if (appendToTextFile(ETCGROUP, "nogroup:x:65534:\n") < 0) {
		iRet=-1;
	    }
	} else {
	    iRet=-2;
	}
    } else {
	iRet=-3;
    }
    
    return iRet;
}

int configure_samba()
{
    int iRet=0;
    char strUpdateSmbConf[MAX_SMB_UPDATE_SIZE];
    
    strUpdateSmbConf[0]='\0';

    strcpy(str_tag1_name, "samba");
    
    // Reading samba global parameters: workgroup, netbios_name
    // Mandatory parameters
    strcpy(str_tag2_name, "global");
    strcpy(str_attribute_name, "workgroup");
    read_attribute();
    if (find_status.value_found == 1) {
    //    printf("%s\n", str_attribute_value);
	sprintf(strUpdateSmbConf, "%sworkgroup = %s\n", strUpdateSmbConf, str_attribute_value);
    } else {
	iRet=-1;
    }
    strcpy(str_attribute_name, "netbios_name");
    read_attribute();
    if (find_status.value_found == 1) {
//        printf("%s\n", str_attribute_value);
	sprintf(strUpdateSmbConf, "%snetbios name = %s\n\n", strUpdateSmbConf, str_attribute_value);
    } else {
	iRet=-1;
    }
    
    int boo;
    if (iRet == 0) {
	for (boo =1; boo > 0; boo++) {
            // Reading samba share parameters: name, path
    	    // Optional parameters
    	    sprintf(str_tag2_name, "share%d", boo);
	    strcpy(str_attribute_name, "name");
    	    read_attribute();
	    if (find_status.value_found == 1) {
//    		printf("%s\n", str_attribute_value);
	        
		sprintf(strUpdateSmbConf, "%s[%s]\n",
		    strUpdateSmbConf, str_attribute_value);

	        strcpy(str_attribute_name, "path");
    		read_attribute();
		if (find_status.value_found == 1) {
//    			printf("%s\n", str_attribute_value);
		    sprintf(strUpdateSmbConf, "%spath = %s\npublic = yes\nwritable = yes\nprintable = no\nguest ok = yes\n\n",
			strUpdateSmbConf, str_attribute_value);
		} else {
		    boo=-1;
	        }
	    } else {
		boo=-1;
	    }
	}
    }
    
    if (appendToTextFile(ETCSMBCONF, strUpdateSmbConf) < 0)
	iRet=-2;
	
    return iRet;
}

int read_attribute()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int psiSize = 0;
    char *pc = NULL;
    psiSize = sysGetPsiSize();
    if ((strXmlBuf = malloc(psiSize)) == NULL) 
    {
	printf("Failed to allocate %d bytes of memory.\n", psiSize);
        return -1;
    }
    sysPersistentGet(strXmlBuf, psiSize, 0);

    // if <psitree> cannot be found then return
    if (memcmp(strXmlBuf, XML_PSI_START_TAG, strlen(XML_PSI_START_TAG)) == 0)
    {
	// determine data length
	pc = strstr(strXmlBuf, XML_PSI_END_TAG);
	if (pc != NULL)
	xmlCfgLen = pc - strXmlBuf + strlen(XML_PSI_END_TAG);
    }
    else
    {
	printf("Invalid configuration data.\n");
	free(strXmlBuf);
	return -1;
    }
    
    xmlSendToParser(strXmlBuf, xmlCfgLen);
    free(strXmlBuf);
    
    return 0;
}

void xmlSendToParser(char *strXml, int strXmlLen)
{
    nxml_t nt_var;
    nxml_settings ns_var;

    ns_var.tag_begin=&my_tag_begin;
    ns_var.attribute_begin=&my_attribute_begin;
    ns_var.attribute_value=&my_attribute_value;
    ns_var.data=&my_data;
    ns_var.tag_end=&my_tag_end;

    parser_status = IDLE;
    init_find_status();
    nxml_open(&nt_var, &ns_var);
    nxml_write(nt_var, strXml, strXmlLen);
    nxml_close(nt_var);
}

void my_tag_begin (nxml_t handle, const char *tag_name, unsigned len)
{
//    printf("Callback tag_begin: %s\n", tag_name);

    int iorlen;
    
    switch (parser_status) {
	case IDLE:
	    iorlen = strlen(PSITREE);
	    if (strncasecmp(PSITREE, tag_name, iorlen)==0) {
		parser_status=PSITREE_FOUND;
//		printf("Tag %s found\n", PSITREE);
	    }
	    break;
	case PSITREE_FOUND:
	    iorlen = strlen(str_tag1_name);
	    if (strncasecmp(str_tag1_name, tag_name, iorlen)==0) {
		parser_status=TAG1BEGIN_FOUND;
		find_status.tag1_found=1;
//		printf("Tag %s found\n", str_tag1_name);
	    }
	    break;
	case TAG1BEGIN_FOUND:
	    iorlen = strlen(str_tag2_name);
	    if (strncasecmp(str_tag2_name, tag_name, iorlen)==0) {
		parser_status=TAG2BEGIN_FOUND;
		find_status.tag2_found=1;
//		printf("Tag %s found\n", str_tag2_name);
	    }
	    break;
    }
}

void my_attribute_begin (nxml_t handle, const char *attr_name, unsigned len)
{
//    printf("Callback attribute_begin: %s\n", attr_name);

    int iorlen;
    
    switch (parser_status) {
	case TAG2BEGIN_FOUND:
	    iorlen = strlen(str_attribute_name);
	    if (strncasecmp(str_attribute_name, attr_name, iorlen)==0) {
		parser_status=ATTRIBUTEBEGIN_FOUND;
		find_status.attribute_found=1;
//		printf("Attribute %s found\n", str_attribute_name);
	    }
	    break;
    }
}

void my_attribute_value (nxml_t handle, const char *attr_value, unsigned len)
{
//    printf("Callback attribute_value: %s\n", attr_value);
    if (len != 0) {
        switch (parser_status) {
    	    case ATTRIBUTEBEGIN_FOUND:
    		strncpy(str_attribute_value, attr_value, len);
		str_attribute_value[len]='\0';
		parser_status=ATTRIBUTEVALUE_FOUND;
		find_status.value_found=1;
//		printf("Value %s found\n", str_attribute_value);

		break;
	}
    }
}

void my_data (nxml_t handle, const char *data, unsigned len)
{
//    printf("Callback data: %s\n", data);
}

void my_tag_end (nxml_t handle, const char *tag_name, unsigned len)
{
//    printf("Callback tag_end: %s\n", tag_name);
    if (len != 0) {
        if (strncasecmp(PSITREE, tag_name, len)==0) {
	    parser_status=END;
	}
    }
}

void init_find_status()
{
    find_status.tag1_found=0;
    find_status.tag2_found=0;
    find_status.attribute_found=0;
    find_status.value_found=0;
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

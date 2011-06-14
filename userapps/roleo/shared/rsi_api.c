#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "board.h"
#include "rsi_api.h"

int boardIoctl(int board_ioctl, BOARD_IOCTL_ACTION action, char *string, int strLen, int offset, char *buf)
{
    BOARD_IOCTL_PARMS IoctlParms;
    int boardFd = 0;
	
    boardFd = open("/dev/brcmboard", O_RDWR);
    if ( boardFd != -1 ) {
	IoctlParms.string = string;
	IoctlParms.strLen = strLen;
	IoctlParms.offset = offset;
	IoctlParms.action = action;
	IoctlParms.buf    = buf;
	ioctl(boardFd, board_ioctl, &IoctlParms);
	close(boardFd);
	boardFd = IoctlParms.result;
    } else {
	printf("Unable to open device /dev/brcmboard.\n");
    }
    
    return boardFd;
}

//********************************************************************************
// Get RSI size
//********************************************************************************
int sysGetRsiSize( void )
{
    return( boardIoctl(BOARD_IOCTL_GET_RSI_SIZE, 0, "", 0, 0, "") );
}

/*****************************************************************************
* sysRsiGet - get the contents of rsi flash memory
* RETURNS: OK, always.
*/
int sysRsiGet(char *string, int strLen, int offset)
{
    return (boardIoctl(BOARD_IOCTL_FLASH_READ, RSI, string, strLen, offset, ""));
}
    
/*****************************************************************************
* sysRsiSet - write the contents of rsi flash memory
* RETURNS: OK, always.
*/
int sysRsiSet(char *string, int strLen, int offset)
{
    return (boardIoctl(BOARD_IOCTL_FLASH_WRITE, RSI, string, strLen, offset, ""));
}

int read_section_bounds(char *rsitree, char *name, char **start, char **end)
{
    static int xmlCfgLen = 0;
    char strStart[64];
    char strEnd[64];
    char *pc = NULL;
    
    // if <rsitree> cannot be found then return
    if (memcmp(rsitree, XML_RSI_START_TAG, strlen(XML_RSI_START_TAG)) == 0)
    {
	// determine data length
	pc = strstr(rsitree, XML_RSI_END_TAG);
	if (pc != NULL)
	xmlCfgLen = pc - rsitree + strlen(XML_RSI_END_TAG);
    }
    else
    {
	printf("Invalid configuration data.\n");
	return -2;
    }
    
    sprintf(strStart, "<%s>", name);
    sprintf(strEnd, "</%s>", name);
    *start = strstr(rsitree, strStart);
    *end = strstr(rsitree, strEnd) + strlen(name) + 2;

    if ((*start == NULL) || (*end == NULL)) return -3;
    
    return 0;
}

int read_attribute()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int rsiSize = 0;
    char *pc = NULL;
    rsiSize = sysGetRsiSize();
    if ((strXmlBuf = malloc(rsiSize)) == NULL) 
    {
	printf("Failed to allocate %d bytes of memory.\n", rsiSize);
        return -1;
    }
    sysRsiGet(strXmlBuf, rsiSize, 0);

    // if <rsitree> cannot be found then return
    if (memcmp(strXmlBuf, XML_RSI_START_TAG, strlen(XML_RSI_START_TAG)) == 0)
    {
	// determine data length
	pc = strstr(strXmlBuf, XML_RSI_END_TAG);
	if (pc != NULL)
	xmlCfgLen = pc - strXmlBuf + strlen(XML_RSI_END_TAG);
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
	    iorlen = strlen(RSITREE);
	    if (strncasecmp(RSITREE, tag_name, iorlen)==0) {
		parser_status=RSITREE_FOUND;
//		printf("Tag %s found\n", RSITREE);
	    }
	    break;
	case RSITREE_FOUND:
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

    int iorlen;
    
    if (len != 0) {
	iorlen = strlen(RSITREE);
        if (strncasecmp(RSITREE, tag_name, iorlen)==0) {
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

// Funtions to handle large attribute: max 8192 byte
int read_attribute_big()
{
    static int xmlCfgLen = 0;
    char *strXmlBuf = NULL;

    int rsiSize = 0;
    char *pc = NULL;
    rsiSize = sysGetRsiSize();
    if ((strXmlBuf = malloc(rsiSize)) == NULL) 
    {
	printf("Failed to allocate %d bytes of memory.\n", rsiSize);
        return -1;
    }
    sysRsiGet(strXmlBuf, rsiSize, 0);

    // if <rsitree> cannot be found then return
    if (memcmp(strXmlBuf, XML_RSI_START_TAG, strlen(XML_RSI_START_TAG)) == 0)
    {
	// determine data length
	pc = strstr(strXmlBuf, XML_RSI_END_TAG);
	if (pc != NULL)
	xmlCfgLen = pc - strXmlBuf + strlen(XML_RSI_END_TAG);
    }
    else
    {
	printf("Invalid configuration data.\n");
	free(strXmlBuf);
	return -1;
    }
    
    xmlSendToParser_big(strXmlBuf, xmlCfgLen);
    free(strXmlBuf);

    return 0;
}

void xmlSendToParser_big(char *strXml, int strXmlLen)
{
    nxml_t nt_var;
    nxml_settings ns_var;

    ns_var.tag_begin=&my_tag_begin;
    ns_var.attribute_begin=&my_attribute_begin;
    ns_var.attribute_value=&my_attribute_value_big;
    ns_var.data=&my_data;
    ns_var.tag_end=&my_tag_end;

    parser_status = IDLE;
    init_find_status();
    nxml_open(&nt_var, &ns_var);
    nxml_write(nt_var, strXml, strXmlLen);
    nxml_close(nt_var);
}

void my_attribute_value_big (nxml_t handle, const char *attr_value, unsigned len)
{
//    printf("Callback attribute_value_big: %s\n", attr_value);
    if (len != 0) {
        switch (parser_status) {
    	    case ATTRIBUTEBEGIN_FOUND:
    		strncpy(str_attribute_value_big, attr_value, len);
		str_attribute_value_big[len]='\0';
		parser_status=ATTRIBUTEVALUE_FOUND;
		find_status.value_found=1;
//		printf("Value %s found\n", str_attribute_value_big);

		break;
	}
    }
}

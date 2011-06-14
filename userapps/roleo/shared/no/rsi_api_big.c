
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

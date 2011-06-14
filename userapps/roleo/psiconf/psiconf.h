#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <psixml.h>
#include "nanoxml.h"

#define PSITREE "psitree"
#define ETCSMBCONF "/etc/samba/smb.conf"
#define ETCPASSWD "/etc/passwd"
#define ETCGROUP "/etc/group"
#define MOUNT "/bin/mount"
#define MAX_SMB_UPDATE_SIZE 1024
#define MAX_PWD_UPDATE_SIZE 256
#define MAX_MOUNT_CMD_SIZE 256

typedef enum {
    IDLE = 0,
    PSITREE_FOUND,
    TAG1BEGIN_FOUND,
    TAG2BEGIN_FOUND,
    ATTRIBUTEBEGIN_FOUND,
    ATTRIBUTEVALUE_FOUND,
    DATA_FOUND,
    TAG1END_FOUND,
    TAG2END_FOUND,
    END
} PARSER_STATUS;

typedef struct {
    int tag1_found;
    int tag2_found;
    int attribute_found;
    int value_found;
} FIND_STATUS;

PARSER_STATUS parser_status;
FIND_STATUS find_status;
char str_tag1_name[NXML_MAX_NAME_SIZE];
char str_tag2_name[NXML_MAX_NAME_SIZE];
char str_attribute_name[NXML_MAX_NAME_SIZE];
char str_attribute_value[NXML_MAX_NAME_SIZE];

void usage(char *strname);
int main(int argc, char*argv[]);
int configure_mount();
int configure_bftpd();
int configure_samba();
int read_attribute();
void xmlSendToParser(char *strXml, int strXmlLen);
//int clean_tag(char *tag_cleaned, char *tag);
void my_tag_begin (nxml_t handle, const char *tag_name, unsigned len);
void my_attribute_begin (nxml_t handle, const char *attr_name, unsigned len);
void my_attribute_value (nxml_t handle, const char *attr_value, unsigned len);
void my_data (nxml_t handle, const char *data, unsigned len);
void my_tag_end (nxml_t handle, const char *tag_name, unsigned len);
void init_find_status();
int appendToTextFile(char *strFilename, char *strPrint);

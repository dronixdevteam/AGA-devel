#include "board.h"
#include "nanoxml.h"

#define XML_RSI_START_TAG	"<rsitree>"
#define XML_RSI_END_TAG		"</rsitree>"
#define NXML_MAX_NAME_SIZE_BIG  16384

#define RSITREE "rsitree"

typedef enum {
    IDLE = 0,
    RSITREE_FOUND,
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
char str_attribute_value_big[NXML_MAX_NAME_SIZE_BIG];

int boardIoctl(int board_ioctl, BOARD_IOCTL_ACTION action, char *string, int strLen, int offset, char *buf);
int sysGetRsiSize( void );
int sysRsiGet(char *string, int strLen, int offset);
int sysRsiSet(char *string, int strLen, int offset);
int read_section_bounds(char *rsitree, char *name, char **start, char **end);
int read_attribute();
void xmlSendToParser(char *strXml, int strXmlLen);

void my_tag_begin (nxml_t handle, const char *tag_name, unsigned len);
void my_attribute_begin (nxml_t handle, const char *attr_name, unsigned len);
void my_attribute_value (nxml_t handle, const char *attr_value, unsigned len);
void my_data (nxml_t handle, const char *data, unsigned len);
void my_tag_end (nxml_t handle, const char *tag_name, unsigned len);
void init_find_status();

int read_attribute_big();
void xmlSendToParser_big(char *strXml, int strXmlLen);
void my_attribute_value_big (nxml_t handle, const char *attr_value, unsigned len);

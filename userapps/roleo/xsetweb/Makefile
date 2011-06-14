# Makefile file for xsetweb by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -DVERSION=\"$(VERSION)\" -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: xsetweb

LIBS= -lpsi -lpsixml

HEADERS=xsetweb.h ../shared/psi_api.h ../shared/util.h ../../broadcom/cfm/inc/board_api.h
OBJS=xsetweb.o ../shared/psi_api.o ../shared/util.o ../../broadcom/cfm/util/psi/board_api.o
SRCS=xsetweb.c ../shared/psi_api.c ../shared/util.c ../../broadcom/cfm/util/psi/board_api.c

install:
	install -m 755 xsetweb $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/xsetweb

dynamic: xsetweb install
	echo $(CFLAGS)

static: xsetweb.a

xsetweb: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o xsetweb

clean:
	-rm -f xsetweb $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)


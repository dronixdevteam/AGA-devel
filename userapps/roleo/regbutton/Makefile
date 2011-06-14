# Makefile
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -DVERSION=\"$(VERSION)\" -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: regbutton

LIBS=-lpsi -lpsixml

HEADERS=regbutton.h ../shared/rsi_api.h ../shared/util.h
OBJS=regbutton.o ../shared/rsi_api.o ../shared/util.o
SRCS=regbutton.c ../shared/rsi_api.c ../shared/util.c

install:
	install -m 755 regbutton $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/regbutton

dynamic: regbutton install
	echo $(CFLAGS)

static: regbutton.a

regbutton: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o regbutton

clean:
	-rm -f regbutton $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)


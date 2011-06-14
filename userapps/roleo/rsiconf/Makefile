# Makefile file for rsiconf by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -DVERSION=\"$(VERSION)\" -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: rsiconf

LIBS= -lpsi -lpsixml -lcrypt

HEADERS=rsiconf.h rsiconfadsl.h ../shared/samba.h ../shared/util.h ../shared/rsi_api.h ../shared/killprocess.h ../shared/passwd.h
OBJS=rsiconf.o rsiconfadsl.o ../shared/samba.o ../shared/util.o ../shared/rsi_api.o ../shared/killprocess.o ../shared/passwd.o
SRCS=rsiconf.c rsiconfadsl.c ../shared/samba.c ../shared/util.c ../shared/rsi_api.c ../shared/killprocess.c ../shared/passwd.c

install:
	install -m 755 rsiconf $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/rsiconf

dynamic: rsiconf install
# install
#	echo $(CFLAGS)

$(BOARD_API_OBJ):	$(INC_BRCMCFM_PATH)/board_api.h
	$(CC) $(CFLAGS) -c $(BOARD_API_SRC)

$(SYSCALL_OBJ):	$(INC_BRCMCFM_PATH)/syscall.h 
	$(CC) $(CFLAGS) -I$(INC_KERNEL_PATH) -I$(INC_KERNEL_PATH2) -c $(SYSCALL_SRC)
		
rsiconf: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o rsiconf

clean:
	-rm -f rsiconf $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)


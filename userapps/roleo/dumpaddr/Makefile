# Makefile file by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: dumpaddr

LIBS=-lpsi

HEADERS=
OBJS=dumpaddr.o
SRCS=dumpaddr.c 

install:
	install -m 755 dumpaddr $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/dumpaddr

dynamic: dumpaddr install

dumpaddr: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o dumpaddr

clean:
	-rm -f dumpaddr $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)


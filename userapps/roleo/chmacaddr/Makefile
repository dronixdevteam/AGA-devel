# Makefile file by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: chmacaddr

LIBS=-lpsi

HEADERS=chmacaddr.h bcm_puzzle.h
OBJS=chmacaddr.o bcm_puzzle.o
SRCS=chmacaddr.c bcm_puzzle.c

install:
	install -m 755 chmacaddr $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/chmacaddr

dynamic: chmacaddr install

chmacaddr: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o chmacaddr

clean:
	-rm -f chmacaddr $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)


# Makefile file by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined

PROG = p910nd
CONFIG = p910nd.conf
#INITSCRIPT = p910nd.init
#MANPAGE = p910nd.8
#INSTALL = install
#BINDIR = /usr/sbin
#CONFIGDIR = /etc/sysconfig
#SCRIPTDIR = /etc/init.d
#MANDIR = /usr/share/man/man8

LIBS=

HEADERS=p910nd.c
OBJS=p910nd.o
SRCS=p910nd.c 

all: p910nd

install:
	install -m 755 $(PROG) $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/p910nd
#	install -m 755 $(CONFIG) $(INSTALL_DIR)/etc

dynamic: p910nd install

p910nd: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o $(PROG)

clean:
	-rm -f $(PROG) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)

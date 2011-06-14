# Makefile by Roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: hotplug

LIBS=-lpsi -lpsixml

HEADERS=hotplug.h ../shared/samba.h ../shared/killprocess.h \
../shared/util.h ../shared/rsi_api.h
OBJS=hotplug.o ../shared/samba.o ../shared/killprocess.o \
../shared/util.o ../shared/rsi_api.o
SRCS=hotplug.c ../shared/samba.c ../shared/killprocess.c \
../shared/util.c ../shared/rsi_api.c

install:
	install -m 755 hotplug $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/hotplug
	install -m 755 original_hotplug $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/original_hotplug
	ln -sf ../bin/hotplug $(INSTALL_DIR)/sbin/hotplug

dynamic: hotplug install
	echo $(CFLAGS)

static: hotplug.a

hotplug: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o hotplug

hotplug.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs hotplug.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f hotplug $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) hotplug.a

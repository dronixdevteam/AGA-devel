# Makefile file for wol by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined
ifeq ($(strip $(BUILD_wol)), static)
CFLAGS += -DBUILD_STATIC
endif

all: wol

LIBS=

HEADERS=wol.h
OBJS=wol.o
SRCS=wol.c 

install:
	install -m 755 wol $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/wol

dynamic: wol install

static: wol.a

wol: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o wol

wol.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs wol.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f wol $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) wol.a


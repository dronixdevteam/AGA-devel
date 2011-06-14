# Makefile file for drun by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined
ifeq ($(strip $(BUILD_DRUN)), static)
CFLAGS += -DBUILD_STATIC
endif

all: drun

LIBS=

HEADERS= 
OBJS=drun.o
SRCS=drun.c 

install:
	install -m 755 drun $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/drun

dynamic: drun install

static: drun.a

drun: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o drun

drun.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs drun.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f drun $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) drun.a


# Makefile file for psiconf by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -DVERSION=\"$(VERSION)\" -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: psiconf

LIBS= -lpsi -lpsixml

HEADERS=psiconf.h
OBJS=psiconf.o
SRCS=psiconf.c

install:
	install -m 755 psiconf $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/psiconf

dynamic: psiconf install
	echo $(CFLAGS)

static: psiconf.a

$(BOARD_API_OBJ):	$(INC_BRCMCFM_PATH)/board_api.h
	$(CC) $(CFLAGS) -c $(BOARD_API_SRC)

$(SYSCALL_OBJ):	$(INC_BRCMCFM_PATH)/syscall.h 
	$(CC) $(CFLAGS) -I$(INC_KERNEL_PATH) -I$(INC_KERNEL_PATH2) -c $(SYSCALL_SRC)
		
psiconf: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o psiconf

psiconf.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs psiconf.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f psiconf $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) psiconf.a


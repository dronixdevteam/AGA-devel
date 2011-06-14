# Makefile file for psiutil by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib
ifeq ($(strip $(BUILD_psiutil)), static)
CFLAGS += -DBUILD_STATIC
endif

all: psiutil

LIBS= -lpsi
#LIBS=

HEADERS=psiutil.h
OBJS=psiutil.o
SRCS=psiutil.c 

install:
	install -m 755 psiutil $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/psiutil

dynamic: psiutil install

static: psiutil.a

psiutil: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o psiutil

psiutil.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs psiutil.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f psiutil $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) psiutil.a


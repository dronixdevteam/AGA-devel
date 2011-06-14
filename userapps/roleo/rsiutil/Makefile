# Makefile file for rsiutil by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib
ifeq ($(strip $(BUILD_rsiutil)), static)
CFLAGS += -DBUILD_STATIC
endif

all: rsiutil rsivalue

LIBS= -lpsi -lpsixml
#LIBS=

HEADERS1=rsiutil.h ../shared/rsi_api.h
OBJS1=rsiutil.o ../shared/rsi_api.o
SRCS1=rsiutil.c ../shared/rsi_api.c
HEADERS2=../shared/rsi_api.h
OBJS2=rsivalue.o ../shared/rsi_api.o
SRCS2=rsivalue.c ../shared/rsi_api.c

install:
	install -m 755 rsiutil $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/rsiutil

dynamic: rsiutil rsivalue install

#install

static: rsiutil.a rsivalue.a

rsiutil: $(HEADERS1) $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o rsiutil

rsivalue: $(HEADERS2) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o rsivalue

rsiutil.a: $(HEADERS1) $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS1)
	$(AR) rcs rsiutil.a $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

rsivalue.a: $(HEADERS2) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS2)
	$(AR) rcs rsivalue.a $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f rsiutil rsivalue $(OBJS1) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ) rsiutil.a rsivalue.a


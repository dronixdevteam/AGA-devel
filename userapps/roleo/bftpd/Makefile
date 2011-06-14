# Makefile file for bftpd
#
# License:  GNU General Public License, Version 2.
#
VERSION=2.2.1
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -DHAVE_CONFIG_H -Wall -DVERSION=\"$(VERSION)\" \
        -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE \
	-I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi

LDFLAGS=-Wl,-allow-shlib-undefined
ifeq ($(strip $(BUILD_FTPD)), static)
CFLAGS += -DBUILD_STATIC
endif

all: bftpd
LIBS= -lcrypt


HEADERS=bftpdutmp.h commands.h commands_admin.h cwd.h dirlist.h list.h login.h logging.h main.h mystring.h options.h targzip.h mypaths.h md5.h md5_loc.h
OBJS=bftpdutmp.o commands.o commands_admin.o cwd.o dirlist.o list.o login.o logging.o main.o mystring.o options.o md5.o
SRCS=bftpdutmp.c commands.c commands_admin.c cwd.c dirlist.c list.c login.c logging.c main.c mystring.c options.c md5.c

#HEADERS=commands.h list.h login.h main.h mystring.h
#OBJS=commands.o list.o login.o main.o mystring.o
#SRCS=commands.c list.c login.c main.c mystring.c
BOARD_API_SRC=$(BROADCOM_CFM_DIR)/util/psi/board_api.c
BOARD_API_OBJ=board_api.o
SYSCALL_SRC=$(BROADCOM_CFM_DIR)/util/system/syscall.c
SYSCALL_OBJ=syscall.o



install:
	install -m 755 bftpd $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/bftpd
	install -m 764 bftpd.conf.default $(INSTALL_DIR)/etc
	cd $(INSTALL_DIR)/etc; rm -f bftpd.conf
	cd $(INSTALL_DIR)/etc; ln -s /var/bftpd.conf bftpd.conf
	


dynamic: bftpd install
	echo $(CFLAGS)


static: bftpd.a

$(BOARD_API_OBJ):	$(INC_BRCMCFM_PATH)/board_api.h
	$(CC) $(CFLAGS) -c $(BOARD_API_SRC)

$(SYSCALL_OBJ):	$(INC_BRCMCFM_PATH)/syscall.h 
	$(CC) $(CFLAGS) -I$(INC_KERNEL_PATH) -I$(INC_KERNEL_PATH2) -c $(SYSCALL_SRC)
		
bftpd: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o bftpd

bftpd.a: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS)
	$(AR) rcs bftpd.a $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

clean:
	-rm -f bftpd $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) bftpd.a


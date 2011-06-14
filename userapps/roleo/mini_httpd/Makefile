# Makefile file for mini_httpd by roleo
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined
ifeq ($(strip $(BUILD_MINI_HTTPD)), static)
CFLAGS += -DBUILD_STATIC
endif

all: mini_httpd

LIBS=-lcrypt

HEADERS=match.h tdate_parse.h version.h mime_encodings.h mime_types.h
OBJS1=mini_httpd.o match.o tdate_parse.o
SRCS1=mini_httpd.c match.c tdate_parse.c
OBJS2=htpasswd.o
SRCS2=htpasswd.c

install:
	install -m 755 mini_httpd $(INSTALL_DIR)/bin/mini_httpd
	install -m 755 htpasswd $(INSTALL_DIR)/bin/htpasswd
	$(STRIP) $(INSTALL_DIR)/bin/mini_httpd
	$(STRIP) $(INSTALL_DIR)/bin/htpasswd

dynamic: mini_httpd htpasswd install

static: mini_httpd.a htpasswd.a

mini_httpd: $(HEADERS) $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o mini_httpd

mini_httpd.a: $(HEADERS) $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS1)
	$(AR) rcs mini_httpd.a $(OBJS1) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

htpasswd: $(HEADERS) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o htpasswd

htpasswd.a: $(HEADERS) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(CFLAGS) -c -o $(OBJS2)
	$(AR) rcs htpasswd.a $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS)

mime_encodings.h: mime_encodings.txt
	rm -f mime_encodings.h
	sed < mime_encodings.txt > mime_encodings.h \
	  -e 's/#.*//' -e 's/[ 	]*$$//' -e '/^$$/d' \
	  -e 's/[ 	][ 	]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'

mime_types.h: mime_types.txt
	rm -f mime_types.h
	sed < mime_types.txt > mime_types.h \
	  -e 's/#.*//' -e 's/[ 	]*$$//' -e '/^$$/d' \
	  -e 's/[ 	][ 	]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'

clean:
	-rm -f mini_httpd htpasswd $(OBJS1) $(OBJS2) $(BOARD_API_OBJ) $(SYSCALL_OBJ) mini_httpd.a htpasswd.a

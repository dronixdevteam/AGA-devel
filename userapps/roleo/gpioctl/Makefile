# Makefile file
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
#CFLAGS += -DBUILD_STATIC

LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

LIBS=

HEADERS=../shared/gpio_api.h
OBJS=gpioctl.o ../shared/gpio_api.o
SRCS=gpioctl.c ../shared/gpio_api.c

all: gpioctl install

install:
	install -m 755 gpioctl $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/gpioctl

gpioctl: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o gpioctl

clean:
	-rm -f gpioctl $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)

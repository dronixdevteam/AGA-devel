# Makefile
#
# License:  GNU General Public License.
#
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I$(INC_BRCMCFM_PATH) \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined -L $(INSTALL_DIR)/lib

all: ethFix install

LIBS=

HEADERS=include/data-traffic.h include/implements.h ../shared/gpio_api.h
OBJS=main.o implements.o ../shared/gpio_api.o
SRCS=main.c implements.c ../shared/gpio_api.c

install:
	install -m 755 ethFix $(INSTALL_DIR)/bin
	$(STRIP) $(INSTALL_DIR)/bin/ethFix

ethFix: $(HEADERS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)
	$(CC) $(LDFLAGS) $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ) $(LIBS) -o ethFix

clean:
	-rm -f ethFix $(OBJS) $(BOARD_API_OBJ) $(SYSCALL_OBJ)

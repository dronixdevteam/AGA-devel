CC = /opt/toolchains/uclibc-crosstools/bin/mips-uclibc-gcc
CFLAGS= -Wall -s -Os -fomit-frame-pointer \
        -I. -I/opt/bcm963xx_router/bcmdrivers/opensource/include/bcm963xx \
        -I$(INC_BRCMDRIVER_PUB_PATH)/$(BRCM_BOARD) -I$(INC_BRCMDRIVER_PRIV_PATH)/$(BRCM_BOARD) \
        -I$(BROADCOM_CFM_DIR)/inc -I$(BROADCOM_CFM_DIR)/util/psi
        
LDFLAGS=-Wl,-allow-shlib-undefined

all: gpio

LIBS=

HEADERS= 
OBJS=gpio.o
SRCS=gpio.c 

dynamic: gpio

gpio: $(HEADERS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o gpio

clean:
	-rm -f gpio $(OBJS)

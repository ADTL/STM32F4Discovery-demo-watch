#*-----------------------------------------------------------------------------
#* Author: Boris Vinogradov(nis) : no111u3@gmail.com
#* File: Makefile
#* Type: Makefile
#* Project: STM32F4D
#* 2013
#*-----------------------------------------------------------------------------
# Project root path
ROOTDIR=$(realpath .)
# Include common config
include lib/make/Makefile.common
# Add another include
CFLAGS+= -I$(ROOTDIR)/lib/xprintf
# Secondary compiler flags
CFLAGS+= -Wl,-T,stm32f4xxxg_flash.ld
# Libs
vpath %.a lib
# Sources and objects
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)
# Rules for compile
all: lib firmware.bin
# Making binary firmware file
%bin: %elf
	$(OBJCOPY) -O binary $^ $@
	$(SIZE) $^
# Making elf
firmware.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBPATHS) $(LIBS)
# Making objects
%.o: $.c
	$(CC) $(CFLAGS) -c -o $@ $^
# Making libs
lib:
	$(MAKE) -C lib ROOTDIR=$(ROOTDIR)
# Rules for clean
clean:
	rm -rf $(OBJS) *.elf *.bin
	$(MAKE) clean -C lib ROOTDIR=$(ROOTDIR) # Remove this line if you don't want to clean the libs as well
# Rules for write firmware to mcu
write: firmware.bin
	qstlink2 -cewV ./firmware.bin
# PHONY
.PHONY: all lib clean
#*-----------------------------------------------------------------------------
#* Author: Boris Vinogradov(nis) : no111u3@gmail.com
#* File: Makefile
#* Type: Makefile
#* Project: STM32F4D
#* 2013
#*-----------------------------------------------------------------------------
# Include common config
include $(ROOTDIR)/lib/make/Makefile.common
# Add local includes
CFLAGS+= -Iinc
# Sources and objects
LIB_SRC_PLATFORM=src/$(PLATFORM)
## Include lib files
SRCS=xprintf.c
OBJS=$(SRCS:.c=.o)
# Library name
LIB=libxprintf.a
# Rules for compile
all: $(LIB)
# Create library
$(LIB): $(OBJS)
	$(AR) -r $(LIB) $(OBJS)
	$(RANLIB) $(LIB)
# Making objects
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^
# Rules for clean
clean:
	-rm -f $(OBJS)
	-rm -f $(LIB)

.PHONY: all clean

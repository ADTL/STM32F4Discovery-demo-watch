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
SRCS+=src/misc.c
# SRCS+=$(LIB_SRC_PLATFORM)_adc.c
# SRCS+=$(LIB_SRC_PLATFORM)_can.c
# SRCS+=$(LIB_SRC_PLATFORM)_crc.c
# SRCS+=$(LIB_SRC_PLATFORM)_cryp.c
# SRCS+=$(LIB_SRC_PLATFORM)_cryp_aes.c
# SRCS+=$(LIB_SRC_PLATFORM)_cryp_des.c
# SRCS+=$(LIB_SRC_PLATFORM)_cryp_tdes.c
# SRCS+=$(LIB_SRC_PLATFORM)_dac.c
# SRCS+=$(LIB_SRC_PLATFORM)_dbgmcu.c
# SRCS+=$(LIB_SRC_PLATFORM)_dcmi.c
# SRCS+=$(LIB_SRC_PLATFORM)_dma.c
SRCS+=$(LIB_SRC_PLATFORM)_exti.c
# SRCS+=$(LIB_SRC_PLATFORM)_flash.c
# SRCS+=$(LIB_SRC_PLATFORM)_fsmc.c
SRCS+=$(LIB_SRC_PLATFORM)_gpio.c
# SRCS+=$(LIB_SRC_PLATFORM)_hash.c
# SRCS+=$(LIB_SRC_PLATFORM)_hash_md5.c
# SRCS+=$(LIB_SRC_PLATFORM)_hash_sha1.c
# SRCS+=$(LIB_SRC_PLATFORM)_i2c.c
# SRCS+=$(LIB_SRC_PLATFORM)_iwdg.c
SRCS+=$(LIB_SRC_PLATFORM)_pwr.c
SRCS+=$(LIB_SRC_PLATFORM)_rcc.c
# SRCS+=$(LIB_SRC_PLATFORM)_rng.c
SRCS+=$(LIB_SRC_PLATFORM)_rtc.c
# SRCS+=$(LIB_SRC_PLATFORM)_sdio.c
SRCS+=$(LIB_SRC_PLATFORM)_spi.c
SRCS+=$(LIB_SRC_PLATFORM)_syscfg.c
SRCS+=$(LIB_SRC_PLATFORM)_tim.c
SRCS+=$(LIB_SRC_PLATFORM)_usart.c
# SRCS+=$(LIB_SRC_PLATFORM)_wwdg.c
OBJS=$(SRCS:.c=.o)
# Library name
LIB=libstdperiph.a
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

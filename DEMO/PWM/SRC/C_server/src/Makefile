# C Application Example for ARM Linux
#  
# Copyright (C) ARM Limited, 2007-2010. All rights reserved.

# This makefile is intended for use with GNU make
#
# This project can be built with either armcc or gcc by setting:
# TOOLCHAIN = armcc
# or
# TOOLCHAIN = gcc

TOOLCHAIN = gcc

TARGET = pwm_dacs
CPU = -march=armv7-a -mcpu=cortex-a8
#CC_OPTS = -c -O3 -g -D M_LITTLE_ENDIAN -mfloat-abi=softfp -pedantic -std=c99 \
		--sysroot="D:\Anton\Work\VMs\VirtualBox\Machines\openSUSE 11.2\Shared Folder\staging_armv7a-angstrom-linux-gnueabi" \
		-Wconversion
#CC_OPTS = -c -g -D M_LITTLE_ENDIAN -mfloat-abi=softfp -pedantic -std=c99\
		--sysroot="D:\Anton\Work\VMs\VirtualBox\Machines\openSUSE 11.2\Shared Folder\staging_armv7a-angstrom-linux-gnueabi" \
		-Wconversion
CC_OPTS = -c -g -D M_LITTLE_ENDIAN -mfloat-abi=softfp -pedantic -std=c99\
		-Wconversion
LINK_OPTS = -lm
OBJS = i2c_drv.o tcpnet.o pwm_drv.o pwm_marshal.o pwm_server.o tcp_marshal.o fpga_drv.o


STRIPPED_DIR = stripped

##########################################################################

CONFIG_FILE =
CPP = arm-none-linux-gnueabi-c++
CC = arm-none-linux-gnueabi-gcc
AR = arm-none-linux-gnueabi-ar
STRIP_APP = arm-none-linux-gnueabi-strip -R .comment --strip-all
STRIP_LIB = arm-none-linux-gnueabi-strip -R .comment --strip-unneeded  


# Select build rules based on Windows or Linux
ifdef WINDIR
WINPATH=$(subst /,\,$(1))
DONE=@if exist $(call WINPATH,$(1)) echo Build completed.
define REAL_RM
if exist $(call WINPATH,$(1)) del /q $(call WINPATH,$(1))

endef
RM=$(foreach file,$(1),$(call REAL_RM,$(file)))
SHELL=$(windir)\system32\cmd.exe
MD=if not exist $(1) mkdir $(1)
CP=copy
else
ifdef windir
WINPATH=$(subst /,\,$(1))
DONE=@if exist $(call WINPATH,$(1)) echo Build completed.
define REAL_RM
if exist $(call WINPATH,$(1)) del /q $(call WINPATH,$(1))

endef
RM=$(foreach file,$(1),$(call REAL_RM,$(file)))
SHELL=$(windir)\system32\cmd.exe
MD=if not exist $(1) mkdir $(1)
CP=copy

else
WINPATH=$(1)
DONE=@if [ -f $(1) ]; then echo Build completed.; fi
RM=rm -f $(1)
MD=@if [ ! -d $(1) ]; then mkdir $(1); fi
CP=cp
endif
endif

##########################################################################

all: $(TARGET)
		$(call DONE,$(TARGET))

rebuild: clean all

clean:
		$(call RM,$(OBJS))
		$(call RM,$(TARGET))
		$(call RM,$(CONFIG_FILE))


# Create the configuration file so that the ARM compiler can find the GCC headers and libraries
$(CONFIG_FILE):
	armcc --arm_linux_configure --arm_linux_config_file=$(CONFIG_FILE)


# Compile the sources
$(OBJS): %.o: %.c $(CONFIG_FILE)
	$(CC) $(CPU) $(CC_OPTS) $< -o $@


# Link the objects together to create an executable
# Strip the host/debug version to create a stripped/nodebug version for downloading to the target
$(TARGET): $(OBJS) $(CONFIG_FILE)
	$(call MD,$(STRIPPED_DIR))
	$(CC) $(LINK_OPTS) $(OBJS) -o $(TARGET)
	$(STRIP_APP) $(TARGET) -o $(STRIPPED_DIR)/$(TARGET)

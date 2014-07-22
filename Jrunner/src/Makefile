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

TARGET = jrunner
CPU = -march=armv7-a
#CC_OPTS = -c -O0 -g
CC_OPTS = -c -g -DBEAGLE_BONE_REVA1 
LINK_OPTS = -lm
OBJS = jb_io.o jb_jtag.o fpga_isp.o jrunner.o
STRIPPED_DIR = stripped

##########################################################################

CONFIG_FILE =
CPP = arm-linux-gnueabi-c++
CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar
STRIP_APP = arm-linux-gnueabi-strip -R .comment --strip-all
STRIP_LIB = arm-linux-gnueabi-strip -R .comment --strip-unneeded  


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

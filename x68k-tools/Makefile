MARSDEV = $(MARS_BUILD_DIR)
MARSCPU = m68k-elf
MARSGCC = $(MARSDEV)/$(MARSCPU)
MARSBIN = $(MARSDEV)/$(MARSCPU)/bin
MARSLIB = $(MARSDEV)/$(MARSCPU)/lib

TARGET = libdos

# GCC and Binutils
CC      = $(MARSBIN)/$(MARSCPU)-gcc
AS      = $(MARSBIN)/$(MARSCPU)-as
AR      = $(MARSBIN)/$(MARSCPU)-ar
RANLIB  = $(MARSBIN)/$(MARSCPU)-ranlib

# LTO plugin path
GCC_VER := $(shell $(CC) -dumpversion)
PLUGIN   = $(MARSGCC)/libexec/gcc/$(MARSCPU)/$(GCC_VER)/liblto_plugin.so

INCS     = -I$(MARSGCC)/lib/gcc/$(MARSCPU)/$(GCC_VER)/include
INCS    += -I$(MARSGCC)/$(MARSCPU)/include
INCS    += -Iinclude

LIBS     = -L$(MARSGCC)/lib/gcc/$(MARSCPU)/$(GCC_VER) -lgcc
LIBS    += -L$(MARSGCC)/$(MARSCPU)/lib -lc -lnosys

CCFLAGS  = -m68000 -std=gnu99 -Wall -Wextra
CCFLAGS += -O2 -fomit-frame-pointer #-flto -fuse-linker-plugin

ASFLAGS := -m68000 --register-prefix-optional --bitwise-or

CS    = $(wildcard *.c)
SS    = $(wildcard *.s)
OBJS  = $(CS:.c=.o)
OBJS += $(SS:.s=.o)

.PHONY: all
all: $(TARGET).a
	cp -f libdos.a $(MARSLIB)/
	cp -f elf2x.py $(MARSBIN)/

%.a: $(OBJS)
	$(AR) rcs --plugin=$(PLUGIN) $@ $(OBJS)
	$(RANLIB) --plugin=$(PLUGIN) $@

%.o: %.c
	$(CC) -o $@ $(CCFLAGS) $(INCS) -c $<

%.o: %.s
	$(AS) -o $@ $(ASFLAGS) $<

.PHONY: test
test: all
	make -C test

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).a

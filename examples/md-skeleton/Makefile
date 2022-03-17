# Sample Makefile for Marsdev (Non-SGDK version)

# Default paths, can be overridden by setting MARSDEV before calling make
MARSDEV ?= ${HOME}/mars
MARSBIN  = $(MARSDEV)/m68k-elf/bin
TOOLSBIN = $(MARSDEV)/bin

# GCC and Binutils
CC   = $(MARSBIN)/m68k-elf-gcc
CXX  = $(MARSBIN)/m68k-elf-g++
AS   = $(MARSBIN)/m68k-elf-as
LD   = $(MARSBIN)/m68k-elf-ld
NM   = $(MARSBIN)/m68k-elf-nm
OBJC = $(MARSBIN)/m68k-elf-objcopy

# Some files needed are in a versioned directory
GCC_VER := $(shell $(CC) -dumpversion)

# Need the LTO plugin so NM can dump our symbol table
PLUGIN   = $(MARSDEV)/m68k-elf/libexec/gcc/m68k-elf/$(GCC_VER)
LTO_SO   = liblto_plugin.so
ifeq ($(OS),Windows_NT)
	LTO_SO = liblto_plugin-0.dll
endif

# Includes: Local + GCC + Newlib
INCS     = -Isrc -Ires -Iinc
INCS    += -I$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include
INCS    += -I$(MARSDEV)/m68k-elf/m68k-elf/include

# Libraries: GCC + Newlib
# If you plan on using Newlib, uncomment the line with -lnosys
LIBS     = -L$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER) -lgcc
#LIBS    += -L$(MARSDEV)/m68k-elf/m68k-elf/lib -lnosys

# Any C or C++ standard should be fine here as long as GCC support it
CCFLAGS  = -m68000 -Wall -Wextra -std=c99 -ffreestanding -fcommon
CXXFLAGS = -m68000 -Wall -Wextra -std=c++17 -ffreestanding

# Extra options set by debug or release target
OPTIONS  = 
ASFLAGS  = -m68000 --register-prefix-optional
LDFLAGS  = -T $(MARSDEV)/ldscripts/md.ld -nostdlib

CS    = $(wildcard src/*.c)
CPPS  = $(wildcard src/*.cpp)
SS    = $(wildcard src/*.s)
OBJS  = $(CS:.c=.o)
OBJS += $(CPPS:.cpp=.o)
OBJS += $(SS:.s=.o)

ASMO  = $(RESS:.res=.o)
ASMO += $(Z80S:.s80=.o)
ASMO += $(CS:%.c=asmout/%.s)

.SECONDARY: out.elf

.PHONY: all release asm debug

all: release

release: OPTIONS  = -O3 -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer
release: OPTIONS += -fshort-enums -flto -fuse-linker-plugin
release: out.bin symbol.txt

asm: OPTIONS  = -O3 -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer
asm: OPTIONS += -fshort-enums
asm: asm-dir $(ASMO)

# Gens-KMod, BlastEm and UMDK support GDB tracing, enabled by this target
debug: OPTIONS = -g -Og -DDEBUG -DKDEBUG
debug: out.bin symbol.txt

# This generates a symbol table that is very helpful in debugging crashes,
# even with an optimized release build!
# Cross reference symbol.txt with the addresses displayed in the crash handler
symbol.txt: out.bin
	$(NM) --plugin=$(PLUGIN)/$(LTO_SO) -n out.elf > symbol.txt

boot.o:
	$(AS) $(ASFLAGS) boot.s -o $@

%.bin: %.elf
	@echo "Stripping ELF header..."
	@$(OBJC) -O binary $< temp.bin
	@dd if=temp.bin of=$@ bs=8192 conv=sync
	@rm -f temp.bin

%.elf: boot.o $(OBJS)
	$(CC) -o $@ $(LDFLAGS) boot.o $(OBJS) $(LIBS)

%.o: %.c
	@echo "CC $<"
	@$(CC) $(CCFLAGS) $(OPTIONS) $(INCS) -c $< -o $@

%.o: %.cpp
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $(OPTIONS) $(INCS) -c $< -o $@

%.o: %.s 
	@echo "AS $<"
	@$(AS) $(ASFLAGS) $< -o $@

# For asm target
asm-dir:
	mkdir -p asmout/src

asmout/%.s: %.c
	$(CC) $(CCFLAGS) $(OPTIONS) $(INCS) -S $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJS) out.bin out.elf symbol.txt boot.o
	rm -rf asmout

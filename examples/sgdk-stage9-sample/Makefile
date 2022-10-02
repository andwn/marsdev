# Sample Makefile for Marsdev (With SGDK, Optional Newlib)

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
# SGDK Tools
RESCOMP = java -jar $(TOOLSBIN)/rescomp.jar
BINTOS   = $(TOOLSBIN)/bintos
PCMTORAW = $(TOOLSBIN)/pcmtoraw
WAVTORAW = $(TOOLSBIN)/wavtoraw
XGMTOOL  = $(TOOLSBIN)/xgmtool

# Some files needed are in a versioned directory
GCC_VER := $(shell $(CC) -dumpversion)

# Need the LTO plugin so NM can dump our symbol table
PLUGIN   = $(MARSDEV)/m68k-elf/libexec/gcc/m68k-elf/$(GCC_VER)
LTO_SO   = liblto_plugin.so
ifeq ($(OS),Windows_NT)
	LTO_SO = liblto_plugin-0.dll
endif

# Includes: Local + GCC + SGDK + Newlib
INCS     = -Isrc -Ires -Iinc
INCS    += -I$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include
INCS    += -I$(MARSDEV)/m68k-elf/include
#INCS    += -I$(MARSDEV)/m68k-elf/m68k-elf/include

# Libraries: GCC + Newlib (SGDK libs are with release/debug targets)
# If you plan on using Newlib, uncomment the line with -lnosys
LIBS     = -L$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER) -lgcc
#LIBS    += -L$(MARSDEV)/m68k-elf/m68k-elf/lib -lnosys

# Force libgcc math routines to be available at link time
LIBS    += -u __modsi3 -u __divsi3 -u __mulsi3 -u __umodsi3 -u __udivsi3 -u __umulsi3

# Any C or C++ standard should be fine here as long as GCC support it
CCFLAGS  = -m68000 -Wall -Wextra -std=c99 -ffreestanding -fcommon
CXXFLAGS = -m68000 -Wall -Wextra -std=c++17 -ffreestanding

# Extra options set by debug or release target
ASFLAGS  = -m68000 --register-prefix-optional

# If you use Newlib, use the link with -nostartfiles instead
LDFLAGS  = -T $(MARSDEV)/ldscripts/sgdk.ld -nostdlib
#LDFLAGS  = -T $(MARSDEV)/ldscripts/sgdk.ld -nostartfiles

RESS  = $(wildcard res/*.res)
CS    = $(wildcard src/*.c)
CPPS  = $(wildcard src/*.cpp)
SS    = $(wildcard src/*.s)

OBJS  = $(RESS:.res=.o)
OBJS += $(CS:.c=.o)
OBJS += $(CPPS:.cpp=.o)
OBJS += $(SS:.s=.o)

ASMO  = $(RESS:.res=.o)
ASMO += $(CS:%.c=asmout/%.s)

.PHONY: all release asm debug
all: release

release: OPTIONS  = -O3 -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer
release: OPTIONS += -fshort-enums -flto -fuse-linker-plugin
release: LIBS += -L$(MARSDEV)/m68k-elf/lib -lmd
release: out.bin symbol.txt

asm: OPTIONS  = -O3 -fno-web -fno-gcse -fno-unit-at-a-time -fomit-frame-pointer
asm: OPTIONS += -fshort-enums
asm: LIBS += -L$(MARSDEV)/m68k-elf/lib -lmd
asm: asm-dir $(ASMO)

# Gens-KMod, BlastEm and UMDK support GDB tracing, enabled by this target
debug: OPTIONS = -g -Og -DDEBUG -DKDEBUG -fno-web -fno-gcse -fno-unit-at-a-time -fshort-enums
debug: LIBS += -L$(MARSDEV)/m68k-elf/lib -lmd-debug
debug: out.bin symbol.txt

# Generates a symbol table that is very helpful in debugging crashes
# Cross reference symbol.txt with the addresses displayed in the crash handler
symbol.txt: out.bin
	@echo "Creating symbol.txt"
	@$(NM) --plugin=$(PLUGIN)/$(LTO_SO) -n out.elf > symbol.txt

boot/sega.o: boot/rom_head.bin
	@echo "AS boot/sega.s"
	@$(CC) $(INCS) -c -x assembler-with-cpp -Wa,-m68000,--register-prefix-optional,--bitwise-or boot/sega.s -o $@

boot/rom_head.bin: boot/rom_head.o
	$(OBJC) -O binary $< $@
	
boot/rom_head.o: boot/rom_head.c
	@echo "CC $<"
	@$(CC) $(CCFLAGS) $(INCS) -c $< -o $@

%.bin: %.elf
	@echo "Stripping ELF header..."
	@$(OBJC) -O binary $< temp.bin
	@dd if=temp.bin of=$@ bs=8K conv=sync
	@rm -f temp.bin

%.elf: boot/sega.o $(OBJS)
	@echo "Linking $@"
	@$(CC) -o $@ $(LDFLAGS) boot/sega.o $(OBJS) $(LIBS)

%.o: %.c
	@echo "CC $<"
	@$(CC) $(CCFLAGS) $(OPTIONS) $(INCS) -c $< -o $@

%.o: %.cpp
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $(OPTIONS) $(INCS) -c $< -o $@

%.o: %.s 
	@echo "AS $<"
	@$(AS) $(ASFLAGS) $< -o $@

%.s: %.res
	$(RESCOMP) $< $@

# For asm target
asm-dir:
	mkdir -p asmout/src

asmout/%.s: %.c
	$(CC) $(CCFLAGS) $(OPTIONS) $(INCS) -S $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) out.bin out.elf symbol.txt
	rm -f boot/sega.o boot/rom_head.o boot/rom_head.bin
	rm -rf asmout

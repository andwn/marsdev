# Sample Makefile for Marsdev (No SGDK, No Newlib)

# Default paths, can be overridden by setting MARSDEV before calling make
MARSDEV ?= /opt/toolchains/mars
MARSBIN  = $(MARSDEV)/m68k-elf/bin

# GCC and Binutils
CC   = $(MARSBIN)/m68k-elf-gcc
CXX  = $(MARSBIN)/m68k-elf-g++
AS   = $(MARSBIN)/m68k-elf-as
LD   = $(MARSBIN)/m68k-elf-ld
NM   = $(MARSBIN)/m68k-elf-nm
OBJC = $(MARSBIN)/m68k-elf-objcopy

# Some files needed are in a versioned directory
GCC_VER := $(shell $(CC) -dumpversion)

# Need the LTO plugin path so NM can dump our symbol table
PLUGIN   = $(MARSDEV)/m68k-elf/libexec/gcc/m68k-elf/$(GCC_VER)
LTO_SO   = liblto_plugin.so
ifeq ($(OS),Windows_NT)
	LTO_SO = liblto_plugin-0.dll
endif

# Includes: Local + GCC
INCS     = -Isrc -Ires -Iinc
INCS    += -I$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include

# Libraries: GCC Only
LIBS     = -L$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER) -lgcc

# Any C or C++ standard should be fine here as long as GCC supports it
# GCC 10+ by default fails to link if you don't declare header variables extern,
# and -fcommon reverts to the old behavior (needed to compile SGDK)
CCFLAGS  = -m68000 -Wall -Wextra -std=c99 -ffreestanding
CXXFLAGS = -m68000 -Wall -Wextra -std=c++17 -ffreestanding

# Another useful GAS flag is --bitwise-or, but it breaks SGDK
ASFLAGS  = -m68000 --register-prefix-optional

# -nostartfiles disables the c runtime startup code
# -nostdlib unsets -lc, so when using Newlib don't set that option
LDFLAGS  = -T megadrive.ld -nostdlib

# Collect source files in the src directory
CS    = $(wildcard src/*.c)
CPPS  = $(wildcard src/*.cpp)
SS    = $(wildcard src/*.s)
OBJS  = $(CS:.c=.o)
OBJS += $(CPPS:.cpp=.o)
OBJS += $(SS:.s=.o)

ASMO  = $(RESS:.res=.o)
ASMO += $(Z80S:.s80=.o)
ASMO += $(CS:%.c=asmout/%.s)

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

# Generates a symbol table that is very helpful in debugging crashes
# Cross reference symbol.txt with the addresses displayed in the crash handler
symbol.txt: out.bin
	@echo "Creating symbol.txt"
	@$(NM) --plugin=$(PLUGIN)/$(LTO_SO) -n out.elf > symbol.txt

%.bin: %.elf
	@echo "Stripping ELF header..."
	@$(OBJC) -O binary $< temp.bin
	@dd if=temp.bin of=$@ bs=8K conv=sync
	@rm -f temp.bin

%.elf: $(OBJS)
	@echo "Linking $@"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

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

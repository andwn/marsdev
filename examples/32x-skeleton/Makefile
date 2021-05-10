# Sample Makefile for Marsdev (32X version)
# For 32X both m68k and SH-2 code has to be built
# The usual variables are split into "MD" and "SH" versions

# Default paths, can be overridden by setting MARSDEV before calling make
MARSDEV ?= ${HOME}/mars
TOOLSBIN = $(MARSDEV)/bin
MDBIN    = $(MARSDEV)/m68k-elf/bin
SHBIN    = $(MARSDEV)/sh-elf/bin

TARGET  ?= example

# m68k GCC and Binutils
MDCC   = $(MDBIN)/m68k-elf-gcc
MDCXX  = $(MDBIN)/m68k-elf-g++
MDAS   = $(MDBIN)/m68k-elf-as
MDLD   = $(MDBIN)/m68k-elf-ld
MDNM   = $(MDBIN)/m68k-elf-nm
MDOBJC = $(MDBIN)/m68k-elf-objcopy
# sh2 GCC and Binutils
SHCC   = $(SHBIN)/sh-elf-gcc
SHCXX  = $(SHBIN)/sh-elf-g++
SHAS   = $(SHBIN)/sh-elf-as
SHLD   = $(SHBIN)/sh-elf-ld
SHNM   = $(SHBIN)/sh-elf-nm
SHOBJC = $(SHBIN)/sh-elf-objcopy

# Some files needed are in a versioned directory
MDCC_VER := $(shell $(MDCC) -dumpversion)
SHCC_VER := $(shell $(SHCC) -dumpversion)

# Need the LTO plugin so NM can dump our symbol table
MDPLUGIN = $(MARSDEV)/m68k-elf/libexec/gcc/m68k-elf/$(MDCC_VER)
SHPLUGIN = $(MARSDEV)/sh-elf/libexec/gcc/sh-elf/$(SHCC_VER)
LTO_SO   = liblto_plugin.so
ifeq ($(OS),Windows_NT)
	LTO_SO = liblto_plugin-0.dll
endif

# m68k Includes: Local + GCC + Newlib
# If you write C code for m68k, make sure that:
#  1. It can be executed from RAM (-fPIC) to avoid blocking SH ROM access
#  2. Don't mix 68k and sh headers/source files, put them in *_md folders
MDINCS   = -Isrc_md -Iinc_md
MDINCS  += -I$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(MDCC_VER)/include
MDINCS  += -I$(MARSDEV)/m68k-elf/m68k-elf/include
# sh2 Includes: Local + GCC + Newlib
SHINCS   = -Isrc -Iinc
SHINCS  += -I$(MARSDEV)/sh-elf/lib/gcc/sh-elf/$(SHCC_VER)/include
SHINCS  += -I$(MARSDEV)/sh-elf/sh-elf/include

# Libraries: GCC + Newlib
# If you plan on using Newlib, uncomment the line with -lnosys
MDLIBS     = -L$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(MDCC_VER) -lgcc
#MDLIBS    += -L$(MARSDEV)/m68k-elf/m68k-elf/lib -lnosys
# Libraries: GCC + Newlib
# The example calls some standard library stuff
SHLIBS     = -L$(MARSDEV)/sh-elf/lib/gcc/sh-elf/$(SHCC_VER) -lgcc
#SHLIBS    += -L$(MARSDEV)/sh-elf/sh-elf/lib -lc -lnosys

# Any C or C++ standard should be fine here as long as GCC support it
MDCCFLAGS  = -m68000 -Wall -Wextra -std=c99 -ffreestanding -fshort-enums
MDCXXFLAGS = -m68000 -Wall -Wextra -std=c++17 -ffreestanding -fshort-enums
SHCCFLAGS  = -m2 -mb -Wall -Wextra -std=c99 -ffreestanding -fshort-enums
SHCXXFLAGS = -m2 -mb -Wall -Wextra -std=c++17 -ffreestanding -fshort-enums

# Assembler flags
MDASFLAGS  = -m68000 --register-prefix-optional
SHASFLAGS  = --small

# Linker flags
MDLDFLAGS  = -T $(MARSDEV)/ldscripts/md.ld -nostdlib
SHLDFLAGS  = -T $(MARSDEV)/ldscripts/mars.ld -nostdlib

# Extra options set by debug or release target
MDEXTRA = 
SHEXTRA = 

# Generate m68k object target list
MDCS    = $(wildcard src_md/*.c)
MDCPPS  = $(wildcard src_md/*.cpp)
MDSS    = $(wildcard src_md/*.s)
MDOBJS  = $(MDCS:.c=.o)
MDOBJS += $(MDCPPS:.cpp=.o)
MDOBJS += $(MDSS:.s=.o)

# Generate sh object target list
SHCS    = $(wildcard src/*.c)
SHCPPS  = $(wildcard src/*.cpp)
SHSS    = $(wildcard src/*.s)
SHOBJS  = boot.o
SHOBJS += $(SHCS:.c=.o)
SHOBJS += $(SHCPPS:.cpp=.o)
SHOBJS += $(SHSS:.s=.o)

.SECONDARY: $(TARGET).elf

.PHONY: all release debug

all: release

release: MDEXTRA  = -Os -fomit-frame-pointer
release: SHEXTRA  = -O3 -fomit-frame-pointer -flto -fuse-linker-plugin
release: m68k_crt0.bin m68k_crt1.bin $(TARGET).32x symbol.txt

# Gens-KMod, BlastEm and UMDK support GDB tracing, enabled by this target
debug: MDEXTRA = -g -Og -DDEBUG -DKDEBUG
debug: SHEXTRA = -g -Og -DDEBUG -DKDEBUG
debug: m68k_crt0.bin m68k_crt1.bin $(TARGET).32x symbol.txt

# This generates a symbol table that is very helpful in debugging crashes,
# even with an optimized release build!
# Cross reference symbol.txt with the addresses displayed in the crash handler
symbol.txt: $(TARGET).32x
	$(SHNM) --plugin=$(SHPLUGIN)/$(LTO_SO) -n $(TARGET).elf > symbol.txt

# m68k stuff

m68k_crt0.bin: m68k_crt0.s
	$(MDAS) $(MDASFLAGS) $< -o $@.o
	$(MDLD) $(MDLDFLAGS) --oformat=binary $@.o -o $@

m68k_crt1.bin: m68k_crt1.s $(MDOBJS)
	$(MDAS) $(MDASFLAGS) m68k_crt1.s -o m68k_crt1.o
	$(MDLD) -nostdlib -T md_crt1.ld --oformat=binary m68k_crt1.o $(MDOBJS) -o m68k_crt1.bin

src_md/%.o: src_md/%.s
	@echo "MDAS $<"
	@$(MDAS) $(MDASFLAGS) $< -o $@

src_md/%.o: src_md/%.c
	@echo "MDCC $<"
	@$(MDCC) $(MDCCFLAGS) $(MDEXTRA) $(MDINCS) -c $< -o $@

src_md/%.o: src_md/%.cpp
	@echo "MDCXX $<"
	@$(MDCXX) $(MDCXXFLAGS) $(MDEXTRA) $(MDINCS) -c $< -o $@

# sh2 stuff

$(TARGET).32x: $(TARGET).elf
	@echo "Stripping ELF header from SH-2 program"
	@$(SHOBJC) -O binary $< temp.32x
	@dd if=temp.32x of=$@ bs=8192 conv=sync
	@rm -f temp.32x

$(TARGET).elf: $(SHOBJS)
	$(SHCC) $(SHLDFLAGS) $(SHOBJS) -o $@ $(SHLIBS)

boot.o: boot.s
	@echo "SHAS $<"
	@$(SHAS) $(SHASFLAGS) $< -o $@

src/%.o: src/%.s 
	@echo "SHAS $<"
	@$(SHAS) $(SHASFLAGS) $< -o $@

src/%.o: src/%.c
	@echo "SHCC $<"
	@$(SHCC) $(SHCCFLAGS) $(SHEXTRA) $(SHINCS) -c $< -o $@

src/%.o: src/%.cpp
	@echo "SHCXX $<"
	@$(SHCXX) $(SHCXXFLAGS) $(SHEXTRA) $(SHINCS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(MDOBJS) $(SHOBJS)
	rm -f m68k_crt0.bin.o m68k_crt1.o m68k_crt0.bin m68k_crt1.bin
	rm -f $(TARGET).32x $(TARGET).elf symbol.txt

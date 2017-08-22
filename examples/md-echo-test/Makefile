GENDEV  ?= ${HOME}/mars
GENBIN   = $(GENDEV)/m68k-elf/bin
TOOLSBIN = $(GENDEV)/bin

# m68k toolchain
CC = $(GENBIN)/m68k-elf-gcc
AS = $(GENBIN)/m68k-elf-as
LD = $(GENBIN)/m68k-elf-ld
NM = $(GENBIN)/m68k-elf-nm
OC = $(GENBIN)/m68k-elf-objcopy

# z80 assembler
AS80 = $(TOOLSBIN)/z80asm

# mdtools
MDTILER = $(TOOLSBIN)/mdtiler
SLZ     = $(TOOLSBIN)/slz
UFTC    = $(TOOLSBIN)/uftc
MML2ESF = $(TOOLSBIN)/mml2esf
PCM2EWF = $(TOOLSBIN)/pcm2ewf
TFI2EIF = $(TOOLSBIN)/tfi2eif

# internal tools
RESGEN = bin/resgen

# versions of all compilers used
GCC_VER     := $(shell gcc -dumpversion)
GENGCC_VER  := $(shell $(CC) -dumpversion)

# Linker plugin path (for nm when LTO is used)
PLUGIN = $(GENDEV)/m68k-elf/libexec/gcc/m68k-elf/$(GENGCC_VER)

# m68k flags
INCS = -Isrc -Ires
LIBS = -L$(GENDEV)/m68k-elf/lib/gcc/m68k-elf/$(GENGCC_VER) -lgcc
CCFLAGS = -m68000 -Wall -Wextra -std=c99 -c -fno-builtin -fshort-enums
ASFLAGS = -m68000 --register-prefix-optional
LDFLAGS = -T $(GENDEV)/ldscripts/sgdk.ld -nostdlib

# resources
RES_AUDIO=$(wildcard res/bgm/*)
RES_AUDIO+=$(wildcard res/fm/*)
RES_AUDIO+=$(wildcard res/pcm/*)
RES_AUDIO+=$(wildcard res/psg/*)

MDT_TSET=$(wildcard res/tset/*.png)
RES_TSET=$(MDT_TSET:.png=.tset)

RESS=res/echoblob.s res/res_audio.s res/res_tset.s
RESH=$(RESS:.s=.h)

CS=$(wildcard src/*.c)
SS=$(wildcard src/*.s)
OBJS=$(CS:.c=.o)
OBJS+=$(SS:.s=.o)
OBJS+=$(RESS:.s=.o)

.PHONY: all release debug clean superclean
.SECONDARY: rom.elf

all: release

release: CCFLAGS += -O3 -fomit-frame-pointer -fno-web -fno-gcse -fno-unit-at-a-time
release: CCFLAGS += -flto -fuse-linker-plugin
release: symbol.txt

debug: CCFLAGS += -g -O2 -DDEBUG -DKDEBUG
debug: symbol.txt

symbol.txt: rom.bin
	@$(NM) --plugin=$(PLUGIN)/liblto_plugin.so -n rom.elf > symbol.txt

# Source build

boot.o:
	@echo "AS $@"
	@$(AS) $(ASFLAGS) boot.s -o $@

%.bin: %.elf
	@$(OC) -O binary $< temp.bin
	@dd if=temp.bin of=$@ bs=8K conv=sync

%.elf: $(RESS) $(OBJS) boot.o
	@echo "LD $@"
	@$(CC) -o $@ $(LDFLAGS) boot.o $(OBJS) $(LIBS)

%.o: %.c
	@echo "CC $<"
	@$(CC) $(CCFLAGS) $(INCS) -c $< -o $@

%.o: %.s
	@echo "AS $<"
	@$(AS) $(ASFLAGS) $< -o $@

# Bundle resource

res/echoblob.s: $(RESGEN) res/echoblob.bin
	$(RESGEN) res/echoblob.bin res/echoblob

res/res_audio.s: $(RESGEN)
	$(RESGEN) $(RES_AUDIO) res/res_audio

res/res_tset.s: $(RES_TSET) $(RESGEN)
	$(RESGEN) $(RES_TSET) res/res_tset

# Convert to resource

res/echoblob.bin: src-z80/build.z80
	$(AS80) -i $< -o $@

%.tset: %.png $(MDTILER)
	$(MDTILER) -t $< $@

# Internal tools

bin:
	mkdir -p bin

$(RESGEN): bin
	gcc tools/resgen/resgen.c -std=c99 -o $@


clean:
	rm -f $(RESS) $(RESH) $(OBJS) res/echoblob.*
	rm -f rom.bin rom.elf temp.bin symbol.txt boot.o

superclean: clean
	rm -rf bin

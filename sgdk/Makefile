ifeq ($(shell which java),)
  $(error "'java' not found. Make sure a Java runtime is installed.")
endif

GDK := $(MARS_BUILD_DIR)/m68k-elf
INC := $(GDK)/inc
BIN := $(GDK)/bin
LIB := $(GDK)/lib

BINTOS         = $(BIN)/bintos
RESCOMP        = $(BIN)/rescomp.jar
XGMTOOL        = $(BIN)/xgmtool
XGMROMBUILDER  = $(BIN)/xgmRomBuilder.jar
SIZEBND        = $(BIN)/sizebnd.jar
LZ4W           = $(BIN)/lz4w.jar
APJ            = $(BIN)/apj.jar

SJASM     = $(BIN)/sjasm
SJBRANCH ?= v0.39

SGDK_VER ?= master
SGDK_OPT ?= default

# Use homebrew's gettext on macOS, for autopoint
ifeq ($(OS),Windows_NT)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		export PATH := /usr/local/opt/gettext/bin:$(PATH)
	endif
endif

# OSX sed fails without the '', and GNU fails with, coolbeans
SED_FIX=
ifeq ($(shell uname -s),Darwin)
	SED_FIX=''
endif

.PHONY: all tools libmd samples clean

all: $(SJASM) SGDK tools libmd

tools: $(BINTOS) $(RESCOMP) $(XGMTOOL) $(XGMROOMBUILDER) $(SIZEBND) $(LZ4W) $(APJ)

libmd: SGDK
	# Copy SGDK files to toolchain
	cp -rf SGDK/inc $(GDK)/
	cp -rf SGDK/res $(GDK)/
	cp -rf SGDK/src $(GDK)/
	cp -f SGDK/common.mk $(GDK)/
	cp -f SGDK/makelib.gen $(GDK)/
	cp -f SGDK/makefile.gen $(GDK)/
	cp -f SGDK/md.ld $(GDK)/
	# release & debug
	#cp -f config-$(SGDK_OPT).h $(INC)/config.h
	$(MAKE) -C $(GDK) -f makelib.gen cleanrelease
	$(MAKE) -C $(GDK) -f makelib.gen release
	$(MAKE) -C $(GDK) -f makelib.gen cleandebug
	$(MAKE) -C $(GDK) -f makelib.gen debug
	# Clean intermediate files only
	$(MAKE) -C $(GDK) -f makelib.gen cleanobj cleandep cleanlst

SGDK:
	git clone --depth=1 --branch $(SGDK_VER) https://github.com/Stephane-D/SGDK
	# Linux native branch in common.mk breaks LTO plugin, this is a workaround
	mv -f SGDK/common.mk SGDK/common.mk.bak
	cp -f common.mk SGDK/common.mk

# SGDK Samples
# If a sample is commented, it fails to build (out of date or special hardware required)

$(GDK)/lib/libmd.a: libmd
	@true

samples: SGDK $(GDK)/lib/libmd.a
	cd SGDK/sample/basics/hello-world && make -f $(GDK)/makefile.gen
	cd SGDK/sample/basics/image && make -f $(GDK)/makefile.gen
	cd SGDK/sample/bench && make -f $(GDK)/makefile.gen
	cd 'SGDK/sample/bitmap/cube 3D' && make -f $(GDK)/makefile.gen
	cd SGDK/sample/bitmap/partic && make -f $(GDK)/makefile.gen
	#cd SGDK/sample/console && make -f $(GDK)/makefile.gen
	cd SGDK/sample/demo/bad-apple && make -f $(GDK)/makefile.gen
	cd SGDK/sample/demo/starfield-donut && make -f $(GDK)/makefile.gen
	#cd SGDK/sample/flash-save && make -f $(GDK)/makefile.gen
	cd SGDK/sample/fx/h-int/scaling && make -f $(GDK)/makefile.gen
	cd SGDK/sample/fx/h-int/wobble && make -f $(GDK)/makefile.gen
	cd SGDK/sample/fx/hilight-shadow && make -f $(GDK)/makefile.gen
	cd SGDK/sample/fx/scroll/linescroll && make -f $(GDK)/makefile.gen
	cd SGDK/sample/joy-test && make -f $(GDK)/makefile.gen
	#cd SGDK/sample/megawifi && make -f $(GDK)/makefile.gen
	cd SGDK/sample/multitasking && make -f $(GDK)/makefile.gen
	#cd SGDK/sample/platformer && make -f $(GDK)/makefile.gen
	cd SGDK/sample/sonic && make -f $(GDK)/makefile.gen
	cd SGDK/sample/sound && make -f $(GDK)/makefile.gen
	#cd SGDK/sample/xgm-player && make -f $(GDK)/makefile.gen

# Tools

$(SJASM):
	rm -rf sjasm
	git clone https://github.com/konamiman/sjasm --depth=1 --branch $(SJBRANCH)
	cd sjasm/Sjasm && $(MAKE)
	cp -f sjasm/Sjasm/sjasm $(SJASM)

$(BINTOS): SGDK
	gcc SGDK/tools/bintos/src/bintos.c -o $@

$(RESCOMP): SGDK
	cp -f SGDK/bin/rescomp.jar $@

$(XGMTOOL): SGDK
	cd SGDK/tools/xgmtool/src && gcc *.c -I../inc -lm -o $@

$(XGMROMBUILDER): SGDK
	cp -f SGDK/bin/xgmRomBuilder.jar $@

$(SIZEBND): SGDK
	cp -f SGDK/bin/sizebnd.jar $@

$(LZ4W): SGDK
	cp -f SGDK/bin/lz4w.jar $@

$(APJ): SGDK
	cp -f SGDK/bin/apj.jar $@

clean:
	rm -rf SGDK sjasm

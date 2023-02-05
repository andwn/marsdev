MARSDEV = $(MARS_BUILD_DIR)
GDK     = $(MARSDEV)/m68k-elf
INC     = $(GDK)/inc
BIN     = $(GDK)/bin
LIB     = $(GDK)/lib

BINTOS         = $(BIN)/bintos
RESCOMP        = $(BIN)/rescomp.jar
XGMTOOL        = $(BIN)/xgmtool
XGMROMBUILDER  = $(BIN)/xgmRomBuilder.jar
SIZEBND        = $(BIN)/sizebnd.jar
LZ4W           = $(BIN)/lz4w.jar
APJ            = $(BIN)/apj.jar

export PATH   := $(BIN):$(PATH)

SGDK_VER ?= master

.PHONY: all tools libmd clean

all: SGDK tools libmd

tools: $(BINTOS) $(RESCOMP) $(XGMTOOL) $(XGMROOMBUILDER) $(SIZEBND) $(LZ4W) $(APJ)

libmd:
	# Copy SGDK files to toolchain
	cp -rf SGDK/inc $(GDK)/
	cp -rf SGDK/res $(GDK)/
	cp -rf SGDK/src $(GDK)/
	cp -f SGDK/common.mk $(GDK)/
	cp -f SGDK/makelib.gen $(GDK)/
	cp -f SGDK/makefile.gen $(GDK)/
	cp -f SGDK/md.ld $(GDK)/
	# Bank switched - release & debug
	cp -f config-far.h $(INC)/config.h
	$(MAKE) -C $(GDK) -f makelib.gen cleanrelease
	$(MAKE) -C $(GDK) -f makelib.gen release
	mv -f $(LIB)/libmd.a $(LIB)/libmd_far.a
	$(MAKE) -C $(GDK) -f makelib.gen cleandebug
	$(MAKE) -C $(GDK) -f makelib.gen debug
	mv -f $(LIB)/libmd_debug.a $(LIB)/libmd_far_debug.a
	# Non-bank switched - release & debug
	cp -f config.h $(INC)/config.h
	$(MAKE) -C $(GDK) -f makelib.gen cleanrelease
	$(MAKE) -C $(GDK) -f makelib.gen release
	$(MAKE) -C $(GDK) -f makelib.gen cleandebug
	$(MAKE) -C $(GDK) -f makelib.gen debug
	# Clean intermediate files only
	$(MAKE) -C $(GDK) -f makelib.gen cleanobj cleandep cleanlst

SGDK:
	git clone --branch $(SGDK_VER) https://github.com/Stephane-D/SGDK
	# Linux native branch in common.mk breaks LTO plugin, this is a workaround
	mv -f SGDK/common.mk SGDK/common.mk.bak
	cp -f common.mk SGDK/common.mk

# Tools

$(BINTOS):
	gcc SGDK/tools/bintos/src/bintos.c -o $@

$(RESCOMP):
	cp -f SGDK/bin/rescomp.jar $@

$(XGMTOOL):
	cd SGDK/tools/xgmtool/src && gcc *.c -I../inc -lm -o $@

$(XGMROMBUILDER):
	cp -f SGDK/bin/xgmRomBuilder.jar $@

$(SIZEBND):
	cp -f SGDK/bin/sizebnd.jar $@

$(LZ4W):
	cp -f SGDK/bin/lz4w.jar $@

$(APJ):
	cp -f SGDK/bin/apj.jar $@

clean:
	rm -rf SGDK

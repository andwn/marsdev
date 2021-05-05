MARSBIN  = $(MARSDEV)/m68k-elf/bin
TOOLSBIN = $(MARSDEV)/bin

BINTOS         = $(TOOLSBIN)/bintos
RESCOMP        = $(TOOLSBIN)/rescomp.jar
XGMTOOL        = $(TOOLSBIN)/xgmtool
XGMROMBUILDER  = $(TOOLSBIN)/xgmRomBuilder.jar
SIZEBND        = $(TOOLSBIN)/sizebnd
LZ4W           = $(TOOLSBIN)/lz4w.jar
APJ            = $(TOOLSBIN)/apj.jar

SGDK_VER ?= v1.62

.PHONY: all tools libmd clean

all: SGDK tools libmd

tools: $(BINTOS) $(RESCOMP) $(XGMTOOL) $(XGMROOMBUILDER) $(SIZEBND) $(LZ4W) $(APJ)

libmd:
	cp -f Makefile.libmd SGDK/Makefile
	if [ -f "config.h" ]; then cp -f config.h SGDK/inc/config.h; fi
	# Release version
	make -C SGDK clean
	make -C SGDK
	cp -f SGDK/libmd.a $(MARSDEV)/m68k-elf/lib/libmd.a
	# Debug version
	make -C SGDK clean
	make -C SGDK debug
	cp -f SGDK/libmd-debug.a $(MARSDEV)/m68k-elf/lib/libmd-debug.a
	# Copy headers
	cp -f SGDK/inc/*.h $(MARSDEV)/m68k-elf/include/
	cp -f SGDK/res/*.h $(MARSDEV)/m68k-elf/include/
	
SGDK:
	git clone --branch $(SGDK_VER) https://github.com/Stephane-D/SGDK

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
	gcc SGDK/tools/sizebnd/src/sizebnd.c -o $@

$(LZ4W):
	cp -f SGDK/bin/lz4w.jar $@

$(APJ):
	cp -f SGDK/bin/apj.jar $@

$(TOOLSBIN):
	mkdir -p $(TOOLSBIN)

clean:
	rm -rf SGDK

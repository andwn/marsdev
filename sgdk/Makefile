MARSBIN  = $(MARSDEV)/m68k-elf/bin
TOOLSBIN = $(MARSDEV)/bin

BINTOS         = $(TOOLSBIN)/bintos
RESCOMP        = $(TOOLSBIN)/rescomp.jar
XGMTOOL        = $(TOOLSBIN)/xgmtool
XGMROMBUILDER  = $(TOOLSBIN)/xgmRomBuilder.jar
SIZEBND        = $(TOOLSBIN)/sizebnd.jar
LZ4W           = $(TOOLSBIN)/lz4w.jar
APJ            = $(TOOLSBIN)/apj.jar

SGDK_VER ?= v1.80

.PHONY: all tools libmd clean

all: SGDK tools libmd

tools: $(BINTOS) $(RESCOMP) $(XGMTOOL) $(XGMROOMBUILDER) $(SIZEBND) $(LZ4W) $(APJ)

libmd:
	cp -f Makefile.libmd SGDK/Makefile
	if [ -f "config.h" ]; then cp -f config.h SGDK/inc/config.h; fi
	# Release version (default)
	$(MAKE) -C SGDK clean
	$(MAKE) -C SGDK
	cp -f SGDK/libmd.a $(MARSDEV)/m68k-elf/lib/libmd.a
	# Debug version (default)
	$(MAKE) -C SGDK clean
	$(MAKE) -C SGDK debug
	cp -f SGDK/libmd-debug.a $(MARSDEV)/m68k-elf/lib/libmd-debug.a
	if [ -f "config-far.h" ]; then cp -f config-far.h SGDK/inc/config.h; fi
	# Release version (bank switch)
	$(MAKE) -C SGDK clean
	$(MAKE) -C SGDK
	cp -f SGDK/libmd.a $(MARSDEV)/m68k-elf/lib/libmd-far.a
	# Debug version (bank switch)
	$(MAKE) -C SGDK clean
	$(MAKE) -C SGDK debug
	cp -f SGDK/libmd-debug.a $(MARSDEV)/m68k-elf/lib/libmd-far-debug.a
	# Copy headers
	cp -f SGDK/inc/*.h $(MARSDEV)/m68k-elf/include/
	cp -f SGDK/res/*.h $(MARSDEV)/m68k-elf/include/
	
SGDK:
	git clone --branch $(SGDK_VER) https://github.com/Stephane-D/SGDK
	# Stef forgot to include stdint so xgmtool fails to compile
	echo "#include <stdint.h>" > incfix.txt
	cat incfix.txt SGDK/tools/xgmtool/src/xgmtool.c > incfix.c
	mv -f incfix.c SGDK/tools/xgmtool/src/xgmtool.c

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

$(TOOLSBIN):
	mkdir -p $(TOOLSBIN)

clean:
	rm -rf SGDK

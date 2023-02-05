# == MARSDEV ==
# Multiplatform Mega Drive toolchain builder and installer
# This is the 'main' Makefile that calls others in their own subdirectories

MARS_BUILD_DIR   ?= $(shell pwd)/mars
MARS_INSTALL_DIR ?= /opt/toolchains/mars
export MARS_BUILD_DIR
export MARS_INSTALL_DIR

.PHONY: m68k-toolchain m68k-toolchain-newlib m68k-toolchain-full m68k-gdb
.PHONY: sh-toolchain sh-toolchain-newlib sh-toolchain-full sh-gdb
.PHONY: all z80-tools sik-tools flamewing-tools x68k-tools sgdk sgdk-samples

all: m68k-toolchain z80-tools sgdk

m68k-toolchain:
	$(MAKE) -C toolchain ARCH=m68k

m68k-toolchain-newlib:
	$(MAKE) -C toolchain all-newlib ARCH=m68k

m68k-toolchain-full:
	$(MAKE) -C toolchain all-newlib ARCH=m68k LANGS=c,c++

m68k-gdb:
	$(MAKE) -C gdb ARCH=m68k

sh-toolchain:
	$(MAKE) -C toolchain ARCH=sh

sh-toolchain-newlib:
	$(MAKE) -C toolchain all-newlib ARCH=sh

sh-toolchain-full:
	$(MAKE) -C toolchain all-newlib ARCH=sh LANGS=c,c++

sh-gdb:
	$(MAKE) -C gdb ARCH=sh

z80-tools:
	$(MAKE) -C z80-tools

sik-tools:
	$(MAKE) -C sik-tools

flamewing-tools:
	$(MAKE) -C flamewing-tools

x68k-tools:
	$(MAKE) -C x68k-tools

sgdk:
	$(MAKE) -C sgdk SGDK_VER=master SGDK_OPT=default

sgdk-samples:
	$(MAKE) -C sgdk samples


.PHONY: install

install:
	@mkdir -p $(MARS_INSTALL_DIR)
	@cp -rf $(MARS_BUILD_DIR)/* $(MARS_INSTALL_DIR)
	@echo "#!/bin/sh" > $(MARS_INSTALL_DIR)/mars.sh
	@echo "export MARSDEV=$(MARS_INSTALL_DIR)" >> $(MARS_INSTALL_DIR)/mars.sh
	@echo "export GDK=$(MARS_INSTALL_DIR)/m68k-elf" >> $(MARS_INSTALL_DIR)/mars.sh
	@chmod +x $(MARS_INSTALL_DIR)/mars.sh
	@echo "Marsdev has been installed to $(MARS_INSTALL_DIR)."
	@echo "Run the following to set the proper environment variables before building your projects:"
	@echo "source $(MARS_INSTALL_DIR)/mars.sh"


.PHONY: clean toolchain-clean gdb-clean tools-clean sgdk-clean

clean: toolchain-clean gdb-clean tools-clean sgdk-clean

toolchain-clean:
	$(MAKE) -C toolchain clean

gdb-clean:
	$(MAKE) -C gdb clean

tools-clean:
	$(MAKE) -C z80-tools clean
	$(MAKE) -C sik-tools clean
	$(MAKE) -C flamewing-tools clean
	$(MAKE) -C x68k-tools clean

sgdk-clean:
	$(MAKE) -C sgdk clean

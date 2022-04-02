# == MARSDEV ==
# Multiplatform Mega Drive toolchain builder and installer
# This is the 'main' Makefile that calls others in their own subdirectories

MARSDEV ?= ${HOME}/mars
export MARSDEV

.PHONY: all m68k-toolchain m68k-toolchain-newlib  sh-toolchain sh-toolchain-newlib
.PHONY: m68k-gdb sh-gdb z80-tools sik-tools flamewing-tools sgdk

all: m68k-toolchain z80-tools sgdk

m68k-toolchain:
	$(MAKE) -C toolchain ARCH=m68k

m68k-toolchain-newlib:
	$(MAKE) -C toolchain all-newlib ARCH=m68k

m68k-gdb:
	$(MAKE) -C gdb ARCH=m68k

sh-toolchain:
	$(MAKE) -C toolchain ARCH=sh

sh-toolchain-newlib:
	$(MAKE) -C toolchain all-newlib ARCH=sh

sh-gdb:
	$(MAKE) -C gdb ARCH=sh

z80-tools:
	$(MAKE) -C z80-tools

sik-tools:
	$(MAKE) -C sik-tools

flamewing-tools:
	$(MAKE) -C flamewing-tools

sgdk:
	$(MAKE) -C sgdk


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

sgdk-clean:
	$(MAKE) -C sgdk clean

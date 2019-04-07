# == MARSDEV ==
# Multiplatform Mega Drive toolchain builder and installer
# This is the 'main' Makefile that calls others in their own subdirectories

export MARSDEV ?= ${HOME}/mars

.PHONY: all $(MAKECMDGOALS)

all: m68k-toolchain z80-tools sgdk

m68k-toolchain:
	make -C toolchain ARCH=m68k

m68k-toolchain-newlib:
	make -C toolchain all-newlib ARCH=m68k

m68k-gdb:
	make -C gdb ARCH=m68k

sh-toolchain:
	make -C toolchain ARCH=sh

sh-toolchain-newlib:
	make -C toolchain all-newlib ARCH=sh

z80-tools:
	make -C z80-tools
	
sik-tools:
	make -C sik-tools

flamewing-tools:
	make -C flamewing-tools

sgdk:
	make -C sgdk SGDK_VER=v1.33

sgdk-master:
	make -C sgdk


clean: toolchain-clean tools-clean sgdk-clean

toolchain-clean:
	make -C toolchain clean

gdb-clean:
	make -C gdb clean

tools-clean:
	make -C z80-tools clean
	make -C sik-tools clean
	make -C flamewing-tools clean

sgdk-clean:
	make -C sgdk clean

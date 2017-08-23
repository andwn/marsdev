export MARSDEV ?= ${HOME}/mars


.PHONY: all m68k-toolchain m68k-gdb sh-toolchain tools sgdk

all: m68k-toolchain tools

m68k-toolchain:
	make -C toolchain ARCH=m68k

m68k-gdb:
	make -C gdb ARCH=m68k

sh-toolchain:
	make -C toolchain ARCH=sh

tools:
	make -C tools

sgdk:
	make -C sgdk


.PHONY: clean toolchain-clean gdb-clean tools-clean sgdk-clean

clean: toolchain-clean tools-clean

toolchain-clean:
	make -C toolchain clean

gdb-clean:
	make -C gdb clean

tools-clean:
	make -C tools clean

sgdk-clean:
	make -C sgdk clean

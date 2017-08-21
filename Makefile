MARSDEV ?= ${HOME}/mars

export


.PHONY: all m68k-toolchain sh-toolchain tools sgdk

all: m68k-toolchain tools

m68k-toolchain:
	make -C toolchain ARCH=m68k

sh-toolchain:
	make -C toolchain ARCH=sh

tools:
	make -C tools

sgdk:
	make -C sgdk


.PHONY: clean toolchain-clean tools-clean sgdk-clean

clean: toolchain-clean tools-clean

toolchain-clean:
	make -C toolchain clean

tools-clean:
	make -C tools clean

sgdk-clean:
	make -C sgdk clean

MARSDEV=${HOME}/mars

GCC_VER      = 7.2.0
BINUTILS_VER = 2.29

export

.PHONY: all m68k-build sh-build tools-build sgdk-build

all: m68k-build sh-build tools-build

m68k-build:
	make -C toolchain ARCH=m68k

sh-build:
	make -C toolchain ARCH=sh

tools-build:
	make -C tools

sgdk-build:
	make -C sgdk

.PHONY: clean toolchain-clean tools-clean sgdk-clean

clean: toolchain-clean tools-clean

toolchain-clean:
	make -C toolchain clean

tools-clean:
	make -C tools clean

sgdk-clean:
	make -C sgdk clean

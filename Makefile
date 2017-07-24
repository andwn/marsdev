MARSDEV=${HOME}/mars

GCC_VER      = 7.1.0
BINUTILS_VER = 2.27
NEWLIB_VER   = 1.19.0

export

all: m68k-build sh-build tools-build sgdk-build

m68k-build:
	make -C toolchain ARCH=m68k

sh-build:
	make -C toolchain ARCH=sh

tools-build:
	make -C tools

sgdk-build:
	make -C sgdk

clean: toolchain-clean tools-clean sgdk-clean

toolchain-clean:
	make -C toolchain clean

tools-clean:
	make -C tools clean

sgdk-clean:
	make -C sgdk clean

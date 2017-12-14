export MARSDEV ?= ${HOME}/mars

.PHONY: all m68k-toolchain m68k-gdb sh-toolchain 
.PHONY: z80-tools sik-tools flamewing-tools sgdk

# Default everything except SH toolchain
all: m68k-toolchain z80-tools sgdk

m68k-toolchain:
	make -C toolchain ARCH=m68k

m68k-gdb:
	make -C gdb ARCH=m68k

sh-toolchain:
	make -C toolchain ARCH=sh

z80-tools:
	make -C z80-tools
	
sik-tools:
	make -C sik-tools

flamewing-tools:
	make -C flamewing-tools

sgdk:
	make -C sgdk


.PHONY: clean toolchain-clean gdb-clean tools-clean sgdk-clean

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

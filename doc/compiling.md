## Compiling Marsdev

Before you begin make sure you followed the installation steps for your OS:
[Windows](install_windows.md) / [MacOS](install_macos.md) / [Linux](install_linux.md)

Clone the repo:
 - `git clone https://github.com/andwn/marsdev`
 - `cd marsdev`

Use make to build the targets you want.
The minimum for a typical SGDK dev is:
 - `make m68k-toolchain`
 - `make z80-tools`
 - `make sgdk`

For 32X dev:
 - `make m68k-toolchain`
 - `make sh-toolchain`
 - `make z80-tools`

The "complete" toolchain the releases use:
 - `make m68k-toolchain-newlib LANGS=c,c++`
 - `make sh-toolchain-newlib LANGS=c,c++`
 - `make z80-tools`
 - `make sgdk`
 - `make sik-tools`
 - `make flamewing-tools`

If everything succeeds you should be all set to copy one of the skeleton projects and start coding.


### Explanation of targets

#### m68k-toolchain

GNU toolchain for Motorola 68000 (Mega Drive), C only, no standard library.

#### sh-toolchain

GNU toolchain for SH-2 (32X and Saturn), C only, no standard library.

#### m68k-toolchain-newlib / sh-toolchain-newlib

Like above but includes the Newlib standard library implementation.
C only by default, but C++ can be included like `LANGS=c,c++`.
Note that due to absurd memory requirements, it is not possible to support the C++ STL.

#### m68k-gdb / sh-gdb

GNU Debuggers for Motorola 68000 or SH-2. I don't use or test these.

#### z80-tools

Currently, just the sjasm Z80 assembler, for building the XGM driver included in SGDK.
Another assembler, z80asm,  used for echo used to be included,
but I'm unable to get it to build on every OS and removed it.

#### sgdk

SGDK and its tools (rescomp, xgmtool, etc).
Builds 2 versions of libmd: `libmd.a` and `libmd-debug.a`

A specific version of SGDK can be specified like `SGDK_VER=<git tag>`,
but I cannot guarantee versions other than the default to work.
Adventurous people who want to test the latest changes can specify `SGDK_VER=master` too.

#### sik-tools

Sik's mdtools that I use fairly often (mdtiler, slz, uftc, echo converters).

#### flamewing-tools

Flamewing's mdcomp and mdtools that are useful for people dealing with Sonic disassemblies.

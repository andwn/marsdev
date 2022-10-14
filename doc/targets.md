# Marsdev Target Reference

Before you begin make sure you followed the [installation steps](install.md).


### Dependencies for all targets

 * Debian: `apt install build-essential texinfo wget`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`
 * Arch: `pacman -S base-devel texinfo wget`
 * Gentoo: `emerge sys-apps/texinfo net-misc/wget`
 * MacOS: `xcode-select --install`


## m68k-toolchain(-newlib) / sh-toolchain(-newlib)

 - `m68k-toolchain` builds a GCC cross compiler toolchain for Motorola 68000 (Mega Drive)
 - `m68k-toolchain-newlib` builds the toolchain with Newlib (C standard library) support
 - `sh-toolchain` and `sh-toolchain-newlib` do the same for SH-2 (32X, Saturn)

It is not necessary to build xx-toolchain before xx-toolchain-newlib,
they are effectively the same target.

Only support for C is built by default because more languages increase compile time significantly.
More languages can be specified after the target in the make command, like `LANGS=c,c++`.

Also by default, the GNU toolchain source packages are downloaded from a mirror I host.
You can specify to grab them from the official GNU/Sourceware servers instead with
`USE_MARS_MIRROR=false`. 

#### Requires Target

None

#### Additional Dependencies

None


## z80-tools

Currently, just the sjasm Z80 assembler, for building the XGM driver included in SGDK.

Requires Target: None


#### Requires Target

None

#### Additional Dependencies

None


## sgdk

SGDK and its tools (rescomp, xgmtool, etc).
Builds four versions of libmd: `libmd.a`, `libmd-debug.a`, `libmd-far.a`, `libmd-far-debug.a`

A specific version of SGDK can be specified like `SGDK_VER=<git tag>`,
but I cannot guarantee versions other than the default to work.
Adventurous people who want to test the latest changes can specify `SGDK_VER=master` too.

#### Requires Target

`m68k-toolchain` `z80-tools`

#### Additional Dependencies

 * Debian: `apt install openjdk-11-jre`
 * RedHat: `yum install java-11-openjdk`
 * Arch: `pacman -S jdk11-openjdk`
 * Gentoo: `emerge dev-java/openjdk`
 * MacOS: `brew install java`
 
(Note: rescomp uses a GUI lib and will crash with headless JDK)


## sik-tools

Sik's mdtools that I use fairly often (mdtiler, slz, uftc, echo converters).

#### Requires Target

None

#### Additional Dependencies

 * Debian: `apt install libpng-dev`
 * RedHat: `yum install libpng-devel`
 * Arch: `pacman -S libpng`
 * Gentoo: `emerge dev-libs/libpng`
 * MacOS: `brew install libpng`

## flamewing-tools

Flamewing's mdcomp and mdtools that are useful for people dealing with Sonic disassemblies.

#### Requires Target

None

#### Additional Dependencies

 * Debian: `apt install cmake libboost-dev`
 * RedHat: `yum install cmake boost-devel`
 * Arch: `pacman -S cmake boost`
 * Gentoo: `emerge dev-libs/boost`
 * MacOS: `brew install cmake boost`


## m68k-gdb / sh-gdb

GNU Debuggers for Motorola 68000 or SH-2. I don't use or test these.

#### Requires Target

`m68k-toolchain` and/or `sh-toolchain`

#### Additional Dependencies

 * Debian: `apt install libgmp-dev`
 * RedHat: `yum install libgmp-devel`
 * Arch: `pacman -S gmp`
 * Gentoo: `emerge dev-libs/gmp`
 

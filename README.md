## Marsdev

Cross platform Mega Drive toolchain and Makefile abuse.


### Dependencies: Windows
 
 * Install [MSYS2](http://www.msys2.org/) and follow the instructions on the site to update it
 * From MinGW 64-bit terminal: `pacman -S make git mingw-w64-x86_64-toolchain texinfo tar diffutils`
   * It should work with the 32-bit terminal too, just replace `x86_64` with `i686`
 * (SGDK Only) Install and configure Java: https://www.java.com/en/download/
   * Take note of where it was installed, then run the following commands making changes as necessary
   * `echo 'export JAVA_HOME="/C/Program Files/Java/jre1.8.0_241"' >> ~/.bash_profile`
   * `echo 'export PATH="${PATH}:${JAVA_HOME}/bin/"' >> ~/.bash_profile`
   * Note that the version in "jre1.8.0_241" will be different for you, and will change each time Java updates


### Dependencies: GNU/Linux

 * Debian: `apt install build-essential texinfo curl`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex`
 * Arch: `pacman -S base-devel texinfo`
 * Gentoo: `emerge sys-apps/texinfo`


### Dependencies: macOS

 * Install the Xcode command line tools
 * Install Java 8 or newer


### Optional Dependencies

 * `sik-tools` requires libpng 1.6
 * `flamewing-tools` requires GNU Autotools, Boost and C++14 support


## Compiling

Clone the repo and run `make`. Make sure you have 3-5GB free disk space.

By default, only `m68k-toolchain`, `z80-tools`, and `sgdk` are installed.
Other targets can be built whenever, just type the name after `make`.

Possible targets to install are:
 * `m68k-toolchain`: GNU toolchain for Motorola 68000 (MegaDrive)
 * `m68k-toolchain-newlib`: Includes Newlib libc implementation, but takes longer to build
   * Note: You may define `LANGS=c,c++` for C++ support (but no STL)
 * `m68k-gdb`: GNU debugger for M68000
 * `sh-toolchain`: GNU toolchain for SH-2 (32X / Saturn)
 * `sh-toolchain-newlib`: Same as `m68k-toolchain-newlib`, but for SH-2
 * `z80-tools`: Z80 Assemblers (just sjasm right now, z80asm is having issues building)
 * `sik-tools`: Sik's mdtools
 * `flamewing-tools`: Flamewing's mdtools, useful for ROM hacking
 * `sgdk`: SGDK and its tools (rescomp, xgmtool, etc)
   * Note: A specific version of SGDK can be specified like `SGDK_VER=<git tag>`
 * `sgdk-legacy`: Shortcut for `sgdk SGDK_VER=v1.33`

The default install path is `${HOME}/mars`, but can be changed by defining `MARSDEV`
like this: `make MARSDEV=/where/to/install`.


## Questions Nobody Asked

### What is the difference between this and the other Genesis/Mega Drive toolchains?

SGDK's bundled toolchain only works on Windows, and Gendev only works on GNU/Linux systems.
I have multiple computers all running different operating systems and it was a huge pain to have
to keep updating multiple build systems for one game. The goal of this toolchain is to avoid
that hassle -- one Makefile in your project that'll build your ROM on any host OS.


### Can I build a Gendev project with Marsdev or vice-versa?

If you're lucky, all you have to do is point GENDEV and MARSDEV to the same place.


### How do I use this with my favorite IDE?

There are so many of these and they all have different places you have to go to configure paths.
In general the only thing you should NEED to do, is point it to the headers.

 * GCC Headers: `$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include`
 * SGDK Headers: `$(MARSDEV)/m68k-elf/include`
 * Newlib Headers: `$(MARSDEV)/m68k-elf/m68k-elf/include`
 
If your IDE lets you configure what the build/run buttons do, just have it run something like this.

 * Build: `MARSDEV=/path/to/mars make`
 * Run: `/path/to/an/emulator out.bin`


### This takes so long to compile!

GCC is a very large lad. We just have to deal with it.


## Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.

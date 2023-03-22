# Marsdev

Cross-platform Mega Drive / 32X / X68K toolchain and Makefile abuse.

English | [日本語](README-ja.md)


## Installation

Follow the [Installation Guide](doc/install.md) to get started.

Marsdev is split into several targets, so you can build just the parts you need.
For more information about each of them, read the [Target Reference](doc/targets.md).


## Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.


## Occasionally Asked Questions

### Too long didn't read I just want to use SGDK on Linux

 - `sudo apt install -y git build-essential texinfo wget openjdk-11-jre`
 - `git clone https://github.com/andwn/marsdev && cd marsdev`
 - `make m68k-toolchain z80-tools sgdk`
 - `sudo make install`
 - Copy out the `examples/sgdk-skeleton` project and start coding.


### What is the difference between this and the other Genesis/Mega Drive toolchains?

In no particular order:

 - SGDK is optional, only bare bones Binutils+GCC are required
 - Newlib support, also optional (*-toolchain-newlib targets)
 - SH-2 toolchain can be built for 32X support
 - Can build most of SGDK's samples
 - Expected to work on ARM hosts
 - (Experimental) Support for creating Human68K programs


### Can I build a Gendev project with Marsdev or vice-versa?

Not easily. Try comparing your Makefile to one of the example projects.


### How do I use this with my favorite IDE?

There are so many of these, and they all have different places you have to go to configure paths.
In general the only thing you should NEED to do, is point it to the headers.

 * GCC Headers: `$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include`
 * SGDK Headers: `$(MARSDEV)/m68k-elf/include`
 * Newlib Headers: `$(MARSDEV)/m68k-elf/m68k-elf/include`
 
If your IDE lets you configure what the build/run buttons do, just have it run something like this.

 * Build: `make MARSDEV=/path/to/mars`
 * Run: `/path/to/an/emulator out.bin`


### I don't have WSL

![Stop using XP](doc/xp.jpg)

MSYS2 might still work, but it's a pain to use and maintain.


### This takes so long to compile!

GCC is a big boy, so we just have to be patient.


# Things to do

 - [x] Self-host a mirror for the toolchain
 - [x] Checksum for downloaded files
 - [x] Fix SGDK skeleton so its Makefile can build Stef's samples
 - [ ] C++ example
 - [ ] この文書化を日本語で翻訳する (Reorganize the English first though)
 - [ ] Include tools necessary for Mega CD and an example project
 - [ ] Write out some information about the C ABI, and how it changes with -mshort
 - [ ] Finish porting the important parts of libdos and getting Newlib to work with it
 - [ ] Investigate Rust support after GCC13 is released

## Marsdev

Cross platform Mega Drive / 32X toolchain and Makefile abuse.


## Installation

(TODO: Reorganize the install/compile docs into just an "Installation Guide" and "Target Reference")

Follow the guide for your OS:
 - [Windows 7/8.1](doc/install_windows.md) (Deprecated, please use WSL instead)
 - [MacOS 10.14+](doc/install_macos.md)
 - [Linux or WSL](doc/install_linux.md)


## Compiling

[Compiling Marsdev](doc/compiling.md)


## Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.


## Occasionally Asked Questions

### Too long didn't read I just want to use SGDK on Linux

 - `sudo apt install -y git build-essential texinfo wget openjdk-11-jre`
 - `git clone https://github.com/andwn/marsdev && cd marsdev`
 - `make m68k-toolchain z80-tools sgdk`
 - Copy out the `examples/sgdk-skeleton` project and start coding.


### What is the difference between this and the other Genesis/Mega Drive toolchains?

SGDK's bundled toolchain only works on Windows, and Gendev only on Linux.
The goal originally was to have something I could use on all of the "big 3" platforms,
but now with WSL it's a moot point and I only have to worry about the Unix-likes.
So here are the main things I am aiming for these days:

 - Keep up to date with GCC and SGDK
 - Support more hosts than just x86_64
 - Make as much of the toolchain optional as possible

The intention of letting users cherry pick targets is to be easy to integrate into
other devkits or frameworks, while also being usable on its own.


### Can I build a Gendev project with Marsdev or vice-versa?

In theory you would only have to set GENDEV and MARSDEV to the same place, but every project is different.


### How do I use this with my favorite IDE?

There are so many of these and they all have different places you have to go to configure paths.
In general the only thing you should NEED to do, is point it to the headers.

 * GCC Headers: `$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include`
 * SGDK Headers: `$(MARSDEV)/m68k-elf/include`
 * Newlib Headers: `$(MARSDEV)/m68k-elf/m68k-elf/include`
 
If your IDE lets you configure what the build/run buttons do, just have it run something like this.

 * Build: `make MARSDEV=/path/to/mars`
 * Run: `/path/to/an/emulator out.bin`


### I don't have WSL

[!Stop using XP](doc/xp.jpg)

There are two supported versions of Windows and both support WSL.
I think that someone who is already insistent on using an out-of-date Windows
should not have any gripes with using an out-of-date toolchain instead of this one.


### This takes so long to compile!

GCC is a big boy so we just have to be patient. Alternatively:

[!Parallel builds](doc/cores.png)


## Things to do

 - [x] Self-host a mirror for the toolchain
 - [x] Checksum for downloaded files
 - [ ] Fix SGDK skeleton so its Makefile can build Stef's samples
 - [ ] C++ example
 - [ ] この文書化を日本語で翻訳する (Reorganize the English first though)
 - [ ] Include tools necessary for Mega CD and an example project
 - [ ] Write out some information about the C ABI, and how it changes with -mshort
 - [ ] Investigate how difficult a Human68k target would be (Xfile binaries, dos.h porting, etc)

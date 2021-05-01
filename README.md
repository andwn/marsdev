## Marsdev

Cross platform Mega Drive / 32X toolchain and Makefile abuse.


## Installation

Follow the guide for your OS:
 - [Windows 7/8.1/10](doc/install_windows.md)
 - [MacOS Mojave/Catalina/Big Sur](doc/install_macos.md)
 - [Linux or WSL](doc/install_linux.md)


## Compiling

[Compiling Marsdev](doc/compiling.md)


## Occasionally Asked Questions

### What is the difference between this and the other Genesis/Mega Drive toolchains?

SGDK's bundled toolchain only works on Windows, and Gendev only works on GNU/Linux systems.
I have multiple computers all running different operating systems and it was a huge pain to have
to keep updating multiple build systems for one game. The goal of this toolchain is to avoid
that hassle -- one Makefile in your project that'll build your ROM on any host OS.


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


### This takes so long to compile!

If I could make it shorter I would, but GCC is a very large lad. We just have to deal with it.


## Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.

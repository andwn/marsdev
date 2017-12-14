## Marsdev

Personal MegaDrive toolchain I put too much effort into.
You probably shouldn't try using this for 32X dev, 
I don't have any examples yet and am still learning how that thing works.


### Install this stuff first (Debian package names)

 * Native GNU toolchain: `build-essential` (GCC >= 5.1.0)
 * GNU Autotools: `libtool` `autoconf` `automake` `autopoint` `gettext`
 * Everything else: `wget` `texinfo` `libpng-dev` (libpng == 1.6)
 * And for SGDK's lz4w compression, `openjdk-8-jre-headless` (Java >= 6)


### Compiling

Clone the repo and run `make`. Make sure you have 3-5GB free disk space.

Possible targets to install are:
 * `m68k-toolchain`: GNU toolchain for Motorola 68000 (MegaDrive)
 * `m68k-gdb`: GNU debugger for M68000
 * `sh-toolchain`: GNU toolchain for SH-2 (32X / Saturn)
 * `z80-tools`: Z80 Assemblers (just sjasm right now, z80asm is having issues building)
 * `sik-tools`: Sik's mdtools
 * `flamewing-tools`: Flamewing's mdtools, useful for ROM hacking
 * `sgdk`: SGDK and its tools (rescomp, xgmtool, etc)

By default, only `m68k-toolchain`, `z80-tools`, and `sgdk` are installed.
Other targets can be built whenever, just type the name after `make`.

The default install path is `${HOME}/mars`, but can be changed by defining `MARSDEV`
like this: `make MARSDEV=/where/to/install`.


### Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.


### TODO

 * 32X example/skeleton

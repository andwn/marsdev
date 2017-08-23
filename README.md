## Marsdev

Personal MegaDrive toolchain I put too much effort into.
You probably shouldn't try using this for 32X dev, 
I don't have any examples yet and am still learning how that thing works.


### Install this stuff first

 * Native GNU toolchain: `build-essential` on Debian/Ubuntu
 * GNU Autotools: `libtool` `autoconf` `automake` `autopoint` `gettext`
 * Everything else: `wget` `texinfo` `libpng16-dev`
 * And if you want SGDK, Java


### Compiling

Clone the repo and run `make`. Make sure you have 3-5GB free disk space.

Possible targets to install are:
 * `m68k-toolchain`: GNU toolchain for Motorola 68000 (MegaDrive)
 * `m68k-gdb`: GNU debugger for M68000
 * `sh-toolchain`: GNU toolchain for SH-2 (32X / Saturn)
 * `tools`: A couple Z80 assemblers and various tools I find useful
 * `sgdk`: SGDK and its tools (rescomp, xgmtool, etc)

By default, only the `m68k-toolchain` and `tools` targets are built.

The default install path is `${HOME}/mars`, but can be changed by defining `MARSDEV`
like this: `make MARSDEV=/where/to/install`.


### Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md].

Naming convention:
 * `md-`: Bare metal MegaDrive project, requires `m68k-toolchain` and `tools`
 * `sgdk-`: SGDK MegaDrive project, requires `m68k-toolchain`, `tools`, and `sgdk`
 * `mars-`: 32X project, requires `m68k-toolchain`, `sh-toolchain`, and `tools`

Should be as easy as a `make` for any of them.


### TODO

 * 32X example/skeleton

## Marsdev

Personal MegaDrive toolchain I put too much effort into.
You probably shouldn't try using this for 32X dev, 
I don't have any examples yet and am still learning how that thing works.

### Dependencies: Windows Users

 * Install [MSYS2](http://www.msys2.org/) and follow the instructions on the site to make sure it is up to date
 * From MinGW 64-bit terminal: `pacman -S mingw-w64-x86_64-toolchain texinfo wget tar diffutils`
 * (It should work with the 32-bit terminal too, just replace `x86_64` with `i686`)


### Dependencies: GNU/Linux Users

 * Arch: `pacman -S base-devel texinfo wget`
 * Debian: `apt install build-essential texinfo wget`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`


### Optional Dependencies

 * `sgdk` needs Java for lz4w compression, but won't fail without it
 * `sik-tools` requires libpng 1.6. Some systems have 1.2 instead which will fail
 * `flamewing-tools` requires the GNU Autotools as well as C++14 support (so GCC >= 5)


### Compiling

Clone the repo and run `make`. Make sure you have 3-5GB free disk space.

By default, only `m68k-toolchain`, `z80-tools`, and `sgdk` are installed.
Other targets can be built whenever, just type the name after `make`.

Possible targets to install are:
 * `m68k-toolchain`: GNU toolchain for Motorola 68000 (MegaDrive)
 * `m68k-gdb`: GNU debugger for M68000
 * `sh-toolchain`: GNU toolchain for SH-2 (32X / Saturn)
 * `z80-tools`: Z80 Assemblers (just sjasm right now, z80asm is having issues building)
 * `sik-tools`: Sik's mdtools
 * `flamewing-tools`: Flamewing's mdtools, useful for ROM hacking
 * `sgdk`: SGDK and its tools (rescomp, xgmtool, etc)

The default install path is `${HOME}/mars`, but can be changed by defining `MARSDEV`
like this: `make MARSDEV=/where/to/install`.


### Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.


### TODO

 * 32X example/skeleton

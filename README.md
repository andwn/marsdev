## Marsdev - GNU toolchain for Genesis + 32X 

It's sort-of working now.


### Install this stuff first

 * Native GNU toolchain: `build-essential` on Debian/Ubuntu
 * GNU Autotools (for z80asm): `libtool` `autoconf` `automake` `gettext`
 * Everything else: `wget` `texinfo` `libpng16-dev`


### Compiling

Clone the repo and run `make`. 
Make sure you have >5GB free disk space, or >15GB if you want C++ too.
By default, only the `m68k-toolchain` and `tools` targets are built.

Some ways you can customize the install:
 * `make MARSDEV=/where/to/install` - Custom install path
 * `make m68k-toolchain sh-toolchain tools sgdk` - Build everything
 * Modify the variable `LANGS` in toolchain/Makefile to support more languages


### How is this different from Gendev?

Added:
 * plugin support for nm, so you can still generate a symbol table with LTO.
 * Most of Sik's tools, and z80asm so Echo can be built.
 * Optional `sh-elf` toolchain for 32X dev.
 * Installs to `${HOME}/mars` by default. No need for superuser.

Not Included:
 * Aplib/Sixpack - Nobody can even get it to build from source. Really.
 * Newlib - All my projects build and run without it. Faster to just skip it.
 * Massive archive files. Don't do that with git.


### TODO

 * SGDK build step (and example project)
 * 32X example project to verify the toolchain is working
 * GDB maybe?

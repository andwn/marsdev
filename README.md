# Marsdev

Cross-platform Mega Drive / 32X / X68K toolchain and Makefile abuse.

English | [日本語](README-ja.md)


## Compile & Install

### 1. Dependencies

Install the following packages, depending on your operating system:
  * Debian: `apt install build-essential texinfo wget`
  * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`
  * Arch: `pacman -S base-devel texinfo wget`
  * Gentoo: `emerge sys-apps/texinfo net-misc/wget`
  * macOS: `xcode-select --install && brew install wget`


### 2. GCC Toolchain

Clone the repo:
 - `git clone https://github.com/andwn/marsdev`
 - `cd marsdev`

---
**NOTE**

There are two variables that control which directory Marsdev is built and installed:
 - `MARS_BUILD_DIR` = (REPOSITORY_ROOT)/mars
 - `MARS_INSTALL_DIR` = /opt/toolchains/mars

If you wish to change the location of either, use an export command like this:
 - `export MARS_INSTALL_DIR=/path/to/mars`

Also by default, the GNU toolchain source packages are downloaded from a mirror I host.
You can specify to grab them from the official GNU/Sourceware servers instead with
`USE_MARS_MIRROR=false`.

---

You have 3 options for building GCC:
 - `make m68k-toolchain` - C support only, without Newlib
 - `make m68k-toolchain-newlib` - C support only, with Newlib
 - `make m68k-toolchain-full` - C and C++ support, with Newlib

For 32X, the `sh` toolchain must also be built.
The options are the same, swapping out `m68k` in the commands above with `sh`.


### 3. (Optional) SGDK

SGDK requires Java, so Install it.
  * Debian: `apt install openjdk-11-jre`
  * RedHat: `yum install java-11-openjdk`
  * Arch: `pacman -S jdk11-openjdk`
  * Gentoo: `emerge dev-java/openjdk`
  * macOS: `brew install java`

---
**Note for macOS**

OpenJDK needs to be added to the PATH.
 - Open `~/.zshrc` (or `~/.bashrc` if you still use bash) and add the line:
    - `export PATH="/usr/local/opt/openjdk/bin:$PATH"`
 - Restart the terminal or run `source ~/.zshrc`

---

Build SGDK:
 - `make sgdk`

A specific version of SGDK can be specified with `SGDK_VER=<git tag>`,
but I cannot guarantee versions other than the default to work.
Adventurous people who want to test the latest changes can specify `SGDK_VER=master` too.

### 4. (Optional) X68000 Tools

You should skip this step if you don't know what a X68000 is.

Build X68k tools:
 - `make x68k-tools`

A GCC/GAS compatible version of libdos is built, along with Newlib glue so the
C runtime can be used on Human68k.


### 5. Install

Just run `sudo make install`. Remember the path to the environment setup script,
and consider adding it to your ~/.bashrc (or ~/.zshrc).


## Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.


## Occasionally Asked Questions

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


### What about Windows?

I highly recommend you use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
and follow the Linux instructions.
As a last resort for those unable to use WSL for whatever reason,
[there is MSYS2](doc/install_msys_legacy.md).
If you don't like any of these options you must really love Windows,
and are better off sticking to vanilla SGDK, as it is meant to be used in Windows.


### This takes so long to compile!

GCC is a big boy, so we just have to be patient.


# Things to do

 - [ ] Finish porting the important parts of libdos and getting Newlib to work with it
 - [ ] Investigate Rust support after GCC13 is released

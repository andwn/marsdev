# Marsdev

Cross-platform Sega Mega Drive / Super 32X / Sharp X68000 toolchain.

English | [日本語](README-ja.md)


## Compile & Install

### 1.1 Dependencies

Install the following packages, depending on your operating system:
  * Debian: `apt install build-essential texinfo wget`
  * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`
  * Arch: `pacman -S base-devel texinfo wget`
  * Gentoo: `emerge sys-apps/texinfo net-misc/wget`
  * macOS: `xcode-select --install && brew install wget`


### 2. GCC Toolchain

Clone the repo:
 - `git clone https://github.com/andwn/marsdev --recurse-submodules`
 - `cd marsdev`

---
**NOTE**

There are two variables that control which directory Marsdev is built and installed:
 - `MARS_BUILD_DIR` = (REPOSITORY_ROOT)/mars
 - `MARS_INSTALL_DIR` = /opt/toolchains/mars

If you wish to change the location of either, use an export command like this:
 - `export MARS_INSTALL_DIR=/path/to/mars`

If you forget `--recurse-submodules` then run:
 - `git submodule init && git submodule update`

Also, it is **highly recommended** to use something like `-j8`, replacing the 8 with
the number of CPU cores you have. I've run into weird unexplainable problems with `-j`
by itself, so please specify a number.

---

You have 2 options for building GCC:
 - `make m68k-toolchain` - Without Newlib
 - `make m68k-toolchain-newlib` - With Newlib

For 32X, the `sh` toolchain must also be built.
The options are the same, swapping out `m68k` in the commands above with `sh`.

If you want a different GCC version, or to build specific languages:
 - `make m68k-toolchain-newlib GCC_VER=12.4.0 LANGS=c,c++`


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

### 4.1 (Optional) Other Tools

The following targets are also available:
 - `make x68k-tools` - Sharp X68000 compatibility
 - `make mdtools-sik` - Contains mdtiler and some Echo stuff (req. libpng)
 - `make mdtools-flamewing` - Compression tools for data in Sonic games (req. boost)

 ### 4.2 (Experimental) LLVM

Need cmake, ninja and python3:
 - Debian: `apt install cmake ninja-build python3`
 - (TODO: Fill in the others)

LLVM with clang for M68k can be built:
 - `make m68k-llvm`
 
Testing hasn't been done yet and examples/skeleton projects still need to be made.


### 5. Install

Just run `sudo make install`. Remember the path to the environment setup script,
and consider adding it to your ~/.bashrc (or ~/.zshrc).


## Examples

The `examples` directory contains various skeleton/example projects to base others on.
For more information on each read [examples/README.md](examples/README.md).

Should be as easy as a `make` for any of them.


## Occasionally Asked Questions

### Whatever man, I just want to use SGDK on Linux

Install:

 - `sudo apt install -y git build-essential texinfo wget openjdk-11-jre`
 - `git clone https://github.com/andwn/marsdev && cd marsdev`
 - `make sgdk -j8`
 - `sudo make install`

Build:

 - Grab the makefile from inside `examples/sgdk-skeleton` and drop it into your project.
 - `source /opt/toolchains/mars/mars.sh`
 - `make`

### Can I build a Gendev project with Marsdev or vice-versa?

Not easily. You'll need to mess with the Makefile to get it working.
Start by comparing your current Makefile to one of the example projects.
The [Migration](doc/migration.md) document may be helpful here.

### How can I tell if an issue I'm having with SGDK is caused by Marsdev?

It should be possible to compile your project as-is with an official SGDK release.
The included Makefile is just a wrapper for `make -f $GDK/makefile.gen`.

If the issue persists, it's SGDK's fault. If the issue is fixed, it's Marsdev's fault.

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

I highly recommend using [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
and follow the instructions for Debian.
You could also try using the Dockerfile, although that is contributed by others
and I don't test it myself.
I used to use [MSYS2](doc/install_msys_legacy.md), but how slow and clunky it is can not be overstated.

An addendum, if you are just here to use SGDK and don't use Linux or macOS then
I think Marsdev will be of little benefit to you anyway.


### I don't like installing to /opt. I want the old ~/mars way back

That's easy.
1. `export MARS_BUILD_DIR=${HOME}/mars`
2. Do steps 1 - 4 normally
3. Skip the installation step, instead add to your `~/.bashrc`:
```
export MARSDEV=${HOME}/mars
export GDK=${MARSDEV}/m68k-elf
```

### This takes so long to compile!

GCC is a big boy, so we just have to be patient.


# Things to do

 - [ ] Finish porting the important parts of libdos and getting Newlib to work with it

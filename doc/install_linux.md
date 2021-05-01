## Installation on Linux

There are many different package managers and I don't use all of them.
Some package names may be off, but you should be able to solve this.


### Dependencies

For the minimal install:
 * Debian: `apt install build-essential texinfo curl`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex`
 * Arch: `pacman -S base-devel texinfo`
 * Gentoo: `emerge sys-apps/texinfo`

If you plan on using `sgdk` (Note: rescomp uses a GUI lib and will crash with headless JDK):
 * Debian: `apt install openjdk-11-jre`
 * RedHat: `yum install java-11-openjdk`
 * Arch: `pacman -S jdk11-openjdk`
 * Gentoo: `emerge dev-java/openjdk`

If you plan on using `sik-tools`:
 * Debian: `apt install libpng-dev`
 * RedHat: `yum install libpng-devel`
 * Arch: `pacman -S libpng`
 * Gentoo: `emerge dev-libs/libpng`

If you plan on using `flamewing-tools`:
 * Debian: `apt install autoconf automake libboost-dev`
 * RedHat: `yum install autoconf automake boost-devel`
 * Arch: `pacman -S autoconf automake boost`
 * Gentoo: `emerge dev-libs/boost`
 
### Option 1: Just extract the latest release

If you download the latest release, you can extract it to your home directory.
Make sure you only have one `mars` folder, `~/mars/mars` is wrong.

That's it. You should be able to build any of the example projects.


### Option 2: Compile the toolchain yourself

Follow the [compilation instructions](compiling.md)

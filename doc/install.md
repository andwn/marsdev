# Marsdev Installation Guide


### Windows Users

I highly recommend you use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
and follow the Linux instructions here.
As a last resort for those unable to use WSL for whatever reason,
[there is MSYS2](install_msys_legacy.md).


### Mac Users

First off, you need the Xcode command line tools (not the whole IDE).
You can install it by running this in your terminal:
 - `xcode-select --install`

I use [homebrew](https://brew.sh/) to install the other packages, so install that.
You're on your own here if you don't want to use homebrew.

For the toolchain, wget is needed to download the tarballs:
 - `brew install wget`

If you plan on using `sgdk`:
 - `brew install java`
 - Open `~/.zshrc` (or `~/.bashrc` if you still use bash) and add the line:
   - `export PATH="/usr/local/opt/openjdk/bin:$PATH"`
 - Restart the terminal or run `source ~/.zshrc`


### Linux / WSL Users

Note: If you don't know what distro you are using, assume it is Ubuntu and try the Debian commands.

For the minimal installation:
 * Debian: `apt install build-essential texinfo wget`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`
 * Arch: `pacman -S base-devel texinfo wget`
 * Gentoo: `emerge sys-apps/texinfo net-misc/wget`

If you plan on using `sgdk`:
 * Debian: `apt install openjdk-11-jre`
 * RedHat: `yum install java-11-openjdk`
 * Arch: `pacman -S jdk11-openjdk`
 * Gentoo: `emerge dev-java/openjdk`


## Compilation

Clone the repo:
 - `git clone https://github.com/andwn/marsdev`
 - `cd marsdev`

---
**NOTE**

There are two variables that control which directory Marsdev is built and installed:
 - `MARS_BUILD_DIR` = (REPOSITORY_ROOT)/mars
 - `MARS_INSTALL_DIR` = /opt/toolchains/mars

If you wish to change the location of either, use an export command like this:

`export MARS_INSTALL_DIR=/path/to/mars`

---

Use make to build the targets you want.
The minimum for a typical SGDK dev is:
 - `make m68k-toolchain`
 - `make z80-tools`
 - `make sgdk`

For 32X dev:
 - `make m68k-toolchain`
 - `make sh-toolchain`
 - `make z80-tools`

The "complete" toolchain the releases use:
 - `make m68k-toolchain-newlib LANGS=c,c++`
 - `make sh-toolchain-newlib LANGS=c,c++`
 - `make z80-tools`
 - `make sgdk`
 - `make sik-tools`
 - `make flamewing-tools`

If everything succeeds you should be all set to copy one of the skeleton projects and start coding.

For more details on what these targets do, check the [Target Reference](targets.md).


## Installation on Windows 7/8.1

These are installation steps for users who do not have access to WSL (Windows Subsystem for Linux),
or people who just prefer not to use it. For WSL, follow the Linux instructions instead.


### Setting up MSYS2 and keeping it up to date

Go visit the [MSYS2](http://www.msys2.org/) website and go through the installer.
Follow the instructions carefully to make sure the packages are up to date.


### Install required packages

Open up a "MSYS2 MinGW 64-bit" terminal and enter the following:
 - `pacman -S make git mingw-w64-x86_64-toolchain texinfo tar wget`

Note: All of these instructions should also work in the 32-bit terminal if you replace `x86_64` with `i686`.

If you plan on using `SGDK`, you need Java 1.8 or newer.
It's a bit annoying to set up, but basically:
 1. Download and run the installer from: https://www.java.com/en/download/
 2. Take note of where it gets installed, and add to `~/.bash_profile`:
   - `export JAVA_HOME="/C/Program Files/Java/jre*/"`
   - `export PATH="${PATH}:${JAVA_HOME}/bin/"`
 3. Run `source ~/.bash_profile` or just close and reopen the terminal

If you plan on using `sik-tools`:
 - `pacman -S mingw-w64-x86_64-libpng`

If you plan on using `flamewing-tools`:
 - `pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-boost`


### Start compiling targets

Check the [Target Reference](targets.md)

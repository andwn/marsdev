## Installation on MacOS

These steps work on my Macbook with Catalina. It should work on Mojave and Big Sur too.
Marsdev does not work on Apple Silicon yet. There are some AArch64 problems to sort out.


### Dependencies

First off, you need the Xcode command line tools (not the whole IDE).
You can install it by running this in your terminal:
 - `xcode-select --install`

I use [homebrew](https://brew.sh/) to install the other packages, so install that.
You're on your own here if you don't want to use homebrew.

If you plan on using `sgdk`:
 - `brew install java`
 - Open `~/.zshrc` (or `~/.bashrc` if you still use bash) and add the line:
   - `export PATH="/usr/local/opt/openjdk/bin:$PATH"`
 - Restart the terminal or run `source ~/.zshrc`

If you plan on using `sik-tools`:
 - `brew install libpng`

If you plan on using `flamewing-tools`:
 - `brew install autoconf automake boost`


### Option 1: Just extract the latest release

If you download the latest release, you can extract it to your home directory.
Make sure you only have one `mars` folder, `~/mars/mars` is wrong.

That's it. You should be able to build any of the example projects.


### Option 2: Compile the toolchain yourself

Follow the [compilation instructions](compiling.md)

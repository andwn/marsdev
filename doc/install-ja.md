# Marsdev Installation Guide （日本語）


### Windows

Windows10か11を持っていれば、[WSL](https://learn.microsoft.com/ja-jp/windows/wsl/install)
でインストールしたほうが良いです。
古い方法は[MSYS2](install_msys_legacy.md)ですけど、私は使ってやめた。


### Mac

最初に、Xcodeのコマンドラインツールが必要です（IDE全体わけではない）。
ターミナルでこれを実行することでインストールできる：
 - `xcode-select --install`

パッケージのインストールには[homebrew](https://brew.sh/)を使っているので、そちらをインストールしてください。
homebrewを使いたくなければ、ここで自己責任でお願いします。

wgetが必要：
 - `brew install wget`

もし`sgdk`をビルドしたい：
 - `brew install java`
 - `~/.zshrc` (まだbashを使用していれば `~/.bashrc`) を開き、次の行を追加して：
   - `export PATH="/usr/local/opt/openjdk/bin:$PATH"`
 - ターミナルを再起動してか、`source ~/.zshrc` を実行して


### Linux / WSL

注：使用しているディストロがわからない場合は、Ubuntuだかもしれない、Debianのコマンドを試してみていい。

いつでも必要なこと：
 * Debian: `apt install build-essential texinfo wget`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`
 * Arch: `pacman -S base-devel texinfo wget`
 * Gentoo: `emerge sys-apps/texinfo net-misc/wget`

`sgdk`ため必要なこと：
 * Debian: `apt install openjdk-11-jre`
 * RedHat: `yum install java-11-openjdk`
 * Arch: `pacman -S jdk11-openjdk`
 * Gentoo: `emerge dev-java/openjdk`


## ツールチェーンビルド

GitHubからクローンして：
 - `git clone https://github.com/andwn/marsdev`
 - `cd marsdev`

---
**注意**

Marsdevがどのディレクトリでビルドされ、インストールされるかを制御する2つの変数がある：
 - `MARS_BUILD_DIR` = (REPOSITORY_ROOT)/mars
 - `MARS_INSTALL_DIR` = /opt/toolchains/mars

どちらかの場所を変更したければ、次のようなエクスポートコマンドを使用できる：

`export MARS_INSTALL_DIR=/path/to/mars`

---

`make`を使用して、必要なターゲットをビルドできる。

SGDKため：
 - `make m68k-toolchain`
 - `make z80-tools`
 - `make sgdk`

32Xため：
 - `make m68k-toolchain`
 - `make sh-toolchain`
 - `make z80-tools`

X68000ため：
- `make m68k-toolchain`
- `make x68k-tools`

全部のツール：
 - `make m68k-toolchain-newlib LANGS=c,c++`
 - `make sh-toolchain-newlib LANGS=c,c++`
 - `make z80-tools`
 - `make sgdk`
 - `make sik-tools`
 - `make x68k-tools`

後で、以下のコマンドでインストールして：

`sudo make install`

すべてが成功すれば、例プロジェクトの1つをコピーして、コーディングを始まるのが整うはずです。

これらのターゲットが何をするのかの詳細については、[ターゲットリファレンス](targets.md)を参照してください。


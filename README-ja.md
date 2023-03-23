# Marsdev

クロスプラットフォームなメガドライブ用ツールチェーンです。

[English](README.md) | 日本語

## ビルドとインストール

### 1. 前提条件

お使いのOSに応じて、以下のパッケージをインストールしてください：
 * Debian: `apt install build-essential texinfo wget`
 * RedHat: `yum install gcc gcc-c++ texinfo-tex wget`
 * Arch: `pacman -S base-devel texinfo wget`
 * Gentoo: `emerge sys-apps/texinfo net-misc/wget`
 * macOS: `xcode-select --install && brew install wget`


### 2. GCC ツールチェーン

GitHubからクローンして：
 - `git clone https://github.com/andwn/marsdev`
 - `cd marsdev`

---
**注意**

Marsdevがどのディレクトリでビルドされ、インストールされるかを制御する2つの変数がある：
 - `MARS_BUILD_DIR` = (REPOSITORY_ROOT)/mars
 - `MARS_INSTALL_DIR` = /opt/toolchains/mars

どちらかの場所を変更したければ、次のようなエクスポートコマンドを使用できる：
 - `export MARS_INSTALL_DIR=/path/to/mars`

また、デフォルトでは、GNUツールチェイン・ソースパッケージは私がホストするミラーからダウンロードされます。
代わりに公式のGNU/Sourcewareサーバから取得するよう、次のように指定できる。
`USE_MARS_MIRROR=false`

---

GCCをビルドするには3つの選択肢がある：
 - `make m68k-toolchain` - Cだけ、Newlibがない
 - `make m68k-toolchain-newlib` - Cだけ、Newlibもある
 - `make m68k-toolchain-full` - CとC++、Newlibもある

32Xためビルドしたければ、`sh-toolchain` も必要です。
選択肢は同じで、上記のコマンドの `m68k` を `sh` に置き換えられる。


### 3. (自由に選択) SGDK

SGDKはJavaを必要とするので、インストールして：
 * Debian: `apt install openjdk-11-jre`
 * RedHat: `yum install java-11-openjdk`
 * Arch: `pacman -S jdk11-openjdk`
 * Gentoo: `emerge dev-java/openjdk`
 * macOS: `brew install java`

---
**注意：macOSについて**

OpenJDKはPATHに追加しなければならない：
 - `~/.zshrc` (まだbashを使用していれば `~/.bashrc`) を開き、次の行を追加して：
    - `export PATH="/usr/local/opt/openjdk/bin:$PATH"`
 - ターミナルを再起動してか、`source ~/.zshrc` を実行して

---

SGDKをビルドして：
 - `make sgdk`

SGDKの特定のバージョンは、`SGDK_VER=<git tag>` で指定できる。
しかし、デフォルト以外のバージョンでの動作は保証できない。
最新の変更をテストしたい冒険者は、`SGDK_VER=master`も指定できる。


### 4. (自由に選択) 他のツール

以下のターゲットも用意されています：
 - `make x68k-tools` - シャープX68000の互換性
 - `make sik-tools` - mdtiler といくつかの Echo を含む (libpng が必要)。
 - `make flamewing-tools` - ソニックゲームのデータ圧縮ツール (cmake + boost が必要)


### 5. インストール

`sudo make install`だけ必要。
説明書のパスを覚えておいて、`~/.bashrc`（または`~/.zshrc`）に追加することを検討してください。


## 例プロジェクト

`examples`というディレクトリには、自分のプロジェクトの基盤となる様々なサンプル・プロジェクトが含まれています。
それぞれの詳細については、[例プロジェクトのREADME](examples/README.md)を参照してください。

ビルドするには、`make`コマンドを実行するのような簡単なはずです。


## 時々聞く質問

### LinuxでSGDKを使いたいだけ。読むのはつまらないなぁ

 - `sudo apt install -y git build-essential texinfo wget openjdk-11-jre`
 - `git clone https://github.com/andwn/marsdev && cd marsdev`
 - `make m68k-toolchain z80-tools sgdk`
 - `sudo make install`
 - そして `examples/sgdk-skeleton` をどこかにコーピーしてコーぢングして始まって。


### どうやってIDEと使えるのだろうか？

色々なIDEがあるんだから、独特の説明できません。
でも、もし設定が見つけられていたら、以下のフォルダーを記入してください。

 * GCC Headers: `$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include`
 * SGDK Headers: `$(MARSDEV)/m68k-elf/include`
 * Newlib Headers: `$(MARSDEV)/m68k-elf/m68k-elf/include`

IDEでビルドとランボタンの動作を設定できるのであれば、以下のように実行させればよい。

 * Build: `make MARSDEV=/path/to/mars`
 * Run: `/path/to/an/emulator out.bin`


### What about Windows?

Windows10か11を持っていれば、[WSL](https://learn.microsoft.com/ja-jp/windows/wsl/install)
でインストールしたほうが良いです。
古い方法は[MSYS2](doc/install_msys_legacy.md)ですけど、私は使ってやめた。


### コンパイルにすごく時間がかかるんだよねー

GCCはとても大きいので、我慢するしかないですね。


# 予定したこと

 - [ ] Finish porting the important parts of libdos and getting Newlib to work with it
 - [ ] Investigate Rust support after GCC13 is released

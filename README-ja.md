# Marsdev

クロスプラットフォームなメガドライブ用ツールチェーンです。

[English](README.md) | 日本語


## インストール方

最初に[インストールガイド](doc/install-ja.md)を読んでください。

Marsdevはいくつかのターゲットに分かれているので、必要な部分だけビルドできます。
それぞれの詳細については、[ターゲットリファレンス](doc/targets.md)にあります。

## 例プロジェクト

`examples`というディレクトリには、自分のプロジェクトの基盤となる様々なサンプル・プロジェクトが含まれています。
それぞれの詳細については、[例プロジェクトのREADME](examples/README-ja.md)を参照してください。

ビルドするには、`make`コマンドを実行するのような簡単なはずです。


## 時々聞く質問

### LinuxでSGDKを使いたいだけ。読むのはつまらないなぁ

 - `sudo apt install -y git build-essential texinfo wget openjdk-11-jre`
 - `git clone https://github.com/andwn/marsdev && cd marsdev`
 - `make m68k-toolchain z80-tools sgdk`
 - `sudo make install`
 - そして `examples/sgdk-skeleton` をどこかにコーピーしてコーぢングして始まって。


### 他のメガドライブ用ツールチェーンと何が違うのでしょうか？

順不同：

- SGDKはオプションで、Binutils+GCCのみ必要です
- Newlib対応、オプション（*-toolchain-newlibというターゲット）もある
- 32X対応のSH-2ツールチェインが構築可能
- SGDKのサンプルのほとんどをビルド可能
- ARMホストでの作業を想定している
- （実験）Human68kのプログラムが作れる


### どうやってIDEと使えるのだろうか？

色々なIDEがあるんだから、独特の説明できません。
でも、もし設定が見つけられていたら、以下のフォルダーを記入してください。

 * GCC Headers: `$(MARSDEV)/m68k-elf/lib/gcc/m68k-elf/$(GCC_VER)/include`
 * SGDK Headers: `$(MARSDEV)/m68k-elf/include`
 * Newlib Headers: `$(MARSDEV)/m68k-elf/m68k-elf/include`

IDEでビルドとランボタンの動作を設定できるのであれば、以下のように実行させればよい。

 * Build: `make MARSDEV=/path/to/mars`
 * Run: `/path/to/an/emulator out.bin`


### WSLを持っていない

![Stop using XP](doc/xp.jpg)

もしSGDKだけを使うのであれば、代わりにGitHubのSGDK公式リポジトリを使ったほうがいいです。
そうでない場合はDockerを使ってみてください。


### コンパイルにすごく時間がかかるんだよねー

GCCはとても大きいので、我慢するしかないですね。


# 予定したこと

 - [x] Self-host a mirror for the toolchain
 - [x] Checksum for downloaded files
 - [x] Fix SGDK skeleton so its Makefile can build Stef's samples
 - [ ] C++ example
 - [ ] この文書化を日本語で翻訳する (Reorganize the English first though)
 - [ ] Include tools necessary for Mega CD and an example project
 - [ ] Write out some information about the C ABI, and how it changes with -mshort
 - [ ] Finish porting the important parts of libdos and getting Newlib to work with it
 - [ ] Investigate Rust support after GCC13 is released

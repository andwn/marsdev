# == MARSDEV ==
# Multiplatform Mega Drive toolchain builder and installer
# This is the 'main' Makefile that calls others in their own subdirectories

MARS_BUILD_DIR   ?= $(shell pwd)/mars
MARS_INSTALL_DIR ?= /opt/toolchains/mars
export MARS_BUILD_DIR
export MARS_INSTALL_DIR

.PHONY: m68k-toolchain m68k-toolchain-newlib m68k-toolchain-full
.PHONY: sh-toolchain sh-toolchain-newlib sh-toolchain-full
.PHONY: all x68k-tools sgdk sgdk-samples

all: m68k-toolchain z80-tools sgdk

m68k-toolchain:
	$(MAKE) -C toolchain ARCH=m68k

m68k-toolchain-newlib:
	$(MAKE) -C toolchain all-newlib ARCH=m68k

m68k-toolchain-full:
	$(MAKE) -C toolchain all-newlib ARCH=m68k LANGS=c,c++

sh-toolchain:
	$(MAKE) -C toolchain ARCH=sh

sh-toolchain-newlib:
	$(MAKE) -C toolchain all-newlib ARCH=sh

sh-toolchain-full:
	$(MAKE) -C toolchain all-newlib ARCH=sh LANGS=c,c++

x68k-tools:
	$(MAKE) -C x68k-tools

sgdk:
	$(MAKE) -C sgdk

sgdk-samples:
	$(MAKE) -C sgdk samples


.PHONY: install

install:
	mkdir -p $(MARS_INSTALL_DIR)
	cp -rf $(MARS_BUILD_DIR)/* $(MARS_INSTALL_DIR)
	echo "#!/bin/sh" > $(MARS_INSTALL_DIR)/mars.sh
	echo "export MARSDEV=$(MARS_INSTALL_DIR)" >> $(MARS_INSTALL_DIR)/mars.sh
	echo "export GDK=$(MARS_INSTALL_DIR)/m68k-elf" >> $(MARS_INSTALL_DIR)/mars.sh
	chmod +x $(MARS_INSTALL_DIR)/mars.sh
	@if [ -z "${LANG##*ja_JP*}" ]; then ;\
	  @echo "Marsdevは$(MARS_INSTALL_DIR)にインストールしました。" ;\
	  @echo "プロジェクトをコンパイルする前に、適切な環境変数を設定するために以下のコマンドを実行してください:" ;\
	else ;\
	  @echo "Marsdev has been installed to $(MARS_INSTALL_DIR)." ;\
	  @echo "Run the following to set the proper environment variables before building your projects:" ;\
	fi
	@echo "source $(MARS_INSTALL_DIR)/mars.sh"


.PHONY: clean toolchain-clean tools-clean sgdk-clean

clean: toolchain-clean tools-clean sgdk-clean

toolchain-clean:
	$(MAKE) -C toolchain clean

tools-clean:
	$(MAKE) -C x68k-tools clean

sgdk-clean:
	$(MAKE) -C sgdk clean

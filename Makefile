# == MARSDEV ==
# Multiplatform Mega Drive toolchain builder and installer
# This is the 'main' Makefile that calls others in their own subdirectories

ifeq ($(shell which makeinfo),)
  $(error "'makeinfo' not found. Make sure the 'texinfo' package is installed.")
endif
ifeq ($(shell which wget),)
  $(error "'wget' not found. Make sure the 'wget' package is installed.")
endif

MARS_BUILD_DIR   ?= $(shell pwd)/mars
MARS_INSTALL_DIR ?= /opt/toolchains/mars
export MARS_BUILD_DIR
export MARS_INSTALL_DIR

GCC_VER  ?= 15.1.0
LLVM_VER ?= main

.PHONY: all
all: sgdk


# Toolchains

.PHONY: m68k-toolchain
m68k-toolchain: m68k-toolchain.d
m68k-toolchain.d: | m68k-gcc-toolchain
	$(MAKE) -C m68k-gcc-toolchain without-newlib GCC_VER=$(GCC_VER)
	$(MAKE) -C m68k-gcc-toolchain install INSTALL_DIR=$(MARS_BUILD_DIR)/m68k-elf
	touch $@

.PHONY: m68k-toolchain-newlib
m68k-toolchain-newlib: m68k-newlib.d
m68k-newlib.d: m68k-toolchain.d | m68k-gcc-toolchain
	$(MAKE) -C m68k-gcc-toolchain all GCC_VER=$(GCC_VER)
	$(MAKE) -C m68k-gcc-toolchain install INSTALL_DIR=$(MARS_BUILD_DIR)/m68k-elf
	touch $@

.PHONY: sh-toolchain
sh-toolchain: sh-toolchain.d
sh-toolchain.d: | sh-gcc-toolchain
	$(MAKE) -C sh-gcc-toolchain without-newlib GCC_VER=$(GCC_VER)
	$(MAKE) -C sh-gcc-toolchain install INSTALL_DIR=$(MARS_BUILD_DIR)/sh-elf
	touch $@

.PHONY: sh-toolchain-newlib
sh-toolchain-newlib: sh-newlib.d
sh-newlib.d: sh-toolchain.d | sh-gcc-toolchain
	$(MAKE) -C sh-gcc-toolchain all GCC_VER=$(GCC_VER)
	$(MAKE) -C sh-gcc-toolchain install INSTALL_DIR=$(MARS_BUILD_DIR)/sh-elf
	touch $@

.PHONY: m68k-llvm
m68k-llvm.d: | llvm-project
	mkdir -p llvm-project/build
	cd llvm-project/build && cmake -G Ninja -D CMAKE_BUILD_TYPE="Release" \
		-D LLVM_EXPERIMENTAL_TARGETS_TO_BUILD="M68k" \
		-D LLVM_ENABLE_PROJECTS="clang" -S ../llvm
	cd llvm-project/build && cmake --build .
	mkdir -p $(MARS_BUILD_DIR)/m68k-elf/llvm
	cp -rf llvm-project/build/bin $(MARS_BUILD_DIR)/m68k-elf/llvm/
	cp -rf llvm-project/build/lib/clang/*/include $(MARS_BUILD_DIR)/m68k-elf/llvm/
	cp -rf llvm-project/build/libexec $(MARS_BUILD_DIR)/m68k-elf/llvm/
	touch $@


# Platform Tools

.PHONY: x68k-tools
x68k-tools: x68k-tools.d
x68k-tools.d: | m68k-newlib.d
	$(MAKE) -C x68k-tools
	touch $@

.PHONY: mdtools-sik sik-tools
sik-tools: mdtools-sik
mdtools-sik: mdtools-sik.d
mdtools-sik.d: | m68k-toolchain.d
	$(MAKE) -C mdtools-sik
	touch $@

.PHONY: mdtools-flamewing flamewing-tools
flamewing-tools: mdtools-flamewing
mdtools-flamewing: mdtools-flamewing.d
mdtools-flamewing.d: | m68k-toolchain.d
	$(MAKE) -C mdtools-flamewing
	touch $@

.PHONY: sgdk
sgdk: sgdk.d
sgdk.d: | m68k-toolchain.d
	$(MAKE) -C sgdk
	touch $@

.PHONY: sgdk-samples
sgdk-samples: | sgdk.d
	$(MAKE) -C sgdk samples


# Intermediate steps

m68k-gcc-toolchain:
	git submodule update --init

sh-gcc-toolchain:
	git submodule update --init

llvm-project:
	git clone https://github.com/llvm/llvm-project --branch $(LLVM_VER) --depth=1


# Install step

.PHONY: install
install:
	@mkdir -p $(MARS_INSTALL_DIR)
	cp -rf $(MARS_BUILD_DIR)/* $(MARS_INSTALL_DIR)
	@echo "#!/bin/sh" > $(MARS_INSTALL_DIR)/mars.sh
	@echo "export MARSDEV=$(MARS_INSTALL_DIR)" >> $(MARS_INSTALL_DIR)/mars.sh
	@echo "export GDK=$(MARS_INSTALL_DIR)/m68k-elf" >> $(MARS_INSTALL_DIR)/mars.sh
	@echo "export PATH=\"$$`echo PATH`:$(MARS_INSTALL_DIR)/m68k-elf/bin\"" >> $(MARS_INSTALL_DIR)/mars.sh
	@echo "export PATH=\"$$`echo PATH`:$(MARS_INSTALL_DIR)/sh-elf/bin\"" >> $(MARS_INSTALL_DIR)/mars.sh
	@chmod +x $(MARS_INSTALL_DIR)/mars.sh
	@echo "--------------------------------------------------------------------------------"
	@if [ ! -z "${LANG##*ja_JP*}" ]; then \
		echo "Marsdevは$(MARS_INSTALL_DIR)にインストールしました。" ;\
		echo "プロジェクトをコンパイルする前に、適切な環境変数を設定するために以下のコマンドを実行してください:" ;\
	else \
		echo "Marsdev has been installed to $(MARS_INSTALL_DIR)." ;\
		echo "Run the following to set the proper environment variables before building your projects:" ;\
	fi
	@echo "source $(MARS_INSTALL_DIR)/mars.sh"
	@echo "--------------------------------------------------------------------------------"


# Clean

.PHONY: clean purge
clean:
	$(MAKE) -C m68k-gcc-toolchain clean
	$(MAKE) -C sh-gcc-toolchain clean
	if [ -d llvm-project ]; then rm -rf llvm-project/build; fi
	$(MAKE) -C mdtools-sik clean
	$(MAKE) -C mdtools-flamewing clean
	$(MAKE) -C x68k-tools clean
	$(MAKE) -C sgdk clean
	rm -rf $(MARS_BUILD_DIR)
	rm -f *.d
	
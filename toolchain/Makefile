GCC_DIR     =gcc-$(GCC_VER)
BINUTILS_DIR=binutils-$(BINUTILS_VER)

GCC_PKG     =$(GCC_DIR).tar.xz
BINUTILS_PKG=$(BINUTILS_DIR).tar.xz

TARGET  = $(ARCH)-elf
PREFIX  = $(MARSDEV)/$(TARGET)
PATH   := $(PREFIX)/bin:$(PATH)
LANGS   = c
LOGDIR := $(shell pwd)

CONFIG_ARGS = --disable-threads --disable-shared --disable-libssp --disable-tls \
			  --disable-nls --disable-werror


.PHONY: all build setup-m68k setup-sh

all: $(GCC_DIR) $(BINUTILS_DIR) build

build: setup-$(ARCH) binutils gcc

setup-m68k: CONFIG_ARGS += --with-cpu=m68000

setup-sh: CONFIG_ARGS += --with-endian=big --with-cpu=m2


.PHONY: binutils gcc

binutils: BUILD_DIR=$(BINUTILS_DIR)/build
binutils:
	@echo "+++ Building $(BINUTILS_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-install-libbfd --disable-nls --disable-werror \
		> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	rm -rf $(BINUTILS_DIR)

gcc: BUILD_DIR=$(GCC_DIR)/build
gcc:
	@echo "+++ Downloading prerequisites to build GCC..."
	cd $(GCC_DIR) && ./contrib/download_prerequisites \
		> $(LOGDIR)/gcc-download-prerequisites-$(ARCH).log 2>&1
	@echo "+++ Building $(GCC_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--without-headers --enable-languages=$(LANGS) $(CONFIG_ARGS) \
		> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	rm -rf $(GCC_DIR)

$(GCC_DIR): $(GCC_PKG)
	tar xf $(GCC_PKG)

$(BINUTILS_DIR): $(BINUTILS_PKG)
	tar xf $(BINUTILS_PKG)

$(GCC_PKG):
	@wget https://mirrors.tripadvisor.com/gnu/gcc/gcc-$(GCC_VER)/$(GCC_PKG)

$(BINUTILS_PKG):
	@wget https://mirrors.tripadvisor.com/gnu/binutils/$(BINUTILS_PKG)


.PHONY: clean

clean:
	rm -rf $(GCC_DIR)
	rm -rf $(BINUTILS_DIR)

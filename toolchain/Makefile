GCC_DIR     =gcc-$(GCC_VER)
BINUTILS_DIR=binutils-$(BINUTILS_VER)
NEWLIB_DIR  =newlib-$(NEWLIB_VER)

GCC_PKG     =$(GCC_DIR).tar.bz2
BINUTILS_PKG=$(BINUTILS_DIR).tar.bz2
NEWLIB_PKG  =$(NEWLIB_DIR).tar.gz

TARGET =$(ARCH)-elf
PREFIX =$(MARSDEV)/$(TARGET)
PATH := $(PREFIX)/bin:$(PATH)
LANGS  =c,c++
LOGDIR := $(shell pwd)

CONFIG_ARGS = --disable-werror


.PHONY: all build setup-m68k setup-sh

all: $(GCC_DIR) $(BINUTILS_DIR) $(NEWLIB_DIR) build

build: setup-$(ARCH) binutils gcc-pass1 newlib gcc-pass2

setup-m68k: CONFIG_ARGS += --with-cpu=m68000

setup-sh: CONFIG_ARGS += --with-endian=big --with-cpu=m2


.PHONY: binutils gcc-pass1 newlib gcc-pass2

binutils: BUILD_DIR=$(BINUTILS_DIR)/build
binutils:
	@echo "+++ Building $(BINUTILS_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-install-libbfd --disable-werror \
		> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	rm -rf $(BINUTILS_DIR)

gcc-pass1: BUILD_DIR=$(GCC_DIR)/build
gcc-pass1:
	@echo "+++ Downloading prerequisites to build GCC..."
	cd $(GCC_DIR) && ./contrib/download_prerequisites \
		> $(LOGDIR)/gcc-download-prerequisites-$(ARCH).log 2>&1
	@echo "+++ Building $(GCC_DIR) for $(ARCH) (pass 1)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--without-headers --with-newlib --enable-languages=c \
		--disable-libssp --disable-tls $(CONFIG_ARGS) \
		> $(LOGDIR)/gcc-pass1-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/gcc-pass1-$(ARCH).log 2>&1

newlib: BUILD_DIR=$(NEWLIB_DIR)/build
newlib:
	@echo "+++ Building $(NEWLIB_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		$(CONFIG_ARGS) > $(LOGDIR)/newlib-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install \
		>> $(LOGDIR)/newlib-$(ARCH).log 2>&1
	rm -rf $(NEWLIB_DIR)

gcc-pass2: BUILD_DIR=$(GCC_DIR)/build
gcc-pass2:
	@echo "+++ Building $(GCC_DIR) for $(ARCH) (pass 2)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-threads=single \
		--with-newlib --enable-languages=$(LANGS) \
		--disable-libssp --disable-tls $(CONFIG_ARGS) \
		> $(LOGDIR)/gcc-pass2-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/gcc-pass2-$(ARCH).log 2>&1
	rm -rf $(GCC_DIR)


$(GCC_DIR): $(GCC_PKG)
	tar xf $(GCC_PKG)

$(BINUTILS_DIR): $(BINUTILS_PKG)
	tar xf $(BINUTILS_PKG)

$(NEWLIB_DIR): $(NEWLIB_PKG)
	tar xf $(NEWLIB_PKG)

$(GCC_PKG):
	@wget http://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VER)/gcc-$(GCC_VER).tar.bz2

$(BINUTILS_PKG):
	@wget http://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VER).tar.bz2

$(NEWLIB_PKG):
	@wget ftp://sourceware.org/pub/newlib/newlib-$(NEWLIB_VER).tar.gz


.PHONY: clean

clean:
	rm -rf $(GCC_DIR)
	rm -rf $(BINUTILS_DIR)
	rm -rf $(NEWLIB_DIR)

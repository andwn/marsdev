GCC_DIR     =gcc-$(GCC_VER)
BINUTILS_DIR=binutils-$(BINUTILS_VER)
NEWLIB_DIR  =newlib-$(NEWLIB_VER)

GCC_PKG     =$(GCC_DIR).tar.bz2
BINUTILS_PKG=$(BINUTILS_DIR).tar.bz2
NEWLIB_PKG  =$(NEWLIB_DIR).tar.gz

TARGET =$(ARCH)-elf
PREFIX =$(MARSDEV)/$(TARGET)
INSTALL=$(PREFIX)/bin
LANGS  =c,c++
THREAD =single
LOGDIR:=$(shell pwd)

CONFIG_ARGS = --disable-werror


.PHONY: all build setup-m68k setup-sh

all: $(GCC_DIR) $(BINUTILS_DIR) $(NEWLIB_DIR) build

build: setup-$(ARCH) binutils gcc-pass1 newlib gcc-pass2

setup-m68k: CONFIG_ARGS += --with-cpu=m68000

setup-sh: CONFIG_ARGS += --with-endian=big --with-cpu=m2


.PHONY: binutils gcc-pass1 newlib gcc-pass2

binutils: BUILDDIR=$(BINUTILS_DIR)/build
binutils:
	@echo "+++ Building $(BINUTILS_DIR) to $(BUILDDIR)..."
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && \
		$(BINUTILS_DIR)/configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-install-libbfd --disable-werror \
		> $(LOGDIR)/binutils-$(ARCH).log
	make -C $(BUILDDIR) all install DESTDIR=$(PREFIX) >> $(LOGDIR)/binutils-$(ARCH).log

gcc-pass1: BUILDDIR=$(GCC_DIR)/build
gcc-pass1:
	@echo "+++ Building $(GCC_DIR) to $(BUILDDIR) (pass 1)..."
	cd $(GCC_DIR) && ./contrib/download_prerequisites \
		> $(LOGDIR)/gcc-download-prerequisites-$(ARCH).log
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && \
		$(GCC_DIR)/configure --target=$(TARGET) --prefix=$(PREFIX) \
		--without-headers --with-newlib --enable-languages=c \
		--disable-libssp --disable-tls $(CONFIG_ARGS) \
		> $(LOGDIR)/gcc-pass1-$(ARCH).log
	make -C $(BUILDDIR) all install DESTDIR=$(PREFIX) >> $(LOGDIR)/gcc-pass1-$(ARCH).log

newlib: BUILDDIR=$(NEWLIB_DIR)/build
newlib:
	@echo "+++ Building $(NEWLIB_DIR) to $(BUILDDIR)..."
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && \
		$(NEWLIB_DIR)/configure --target=$(TARGET) --prefix=$(PREFIX) \
		$(CONFIG_ARGS) > $(LOGDIR)/gcc-pass1-$(ARCH).log
	make -C $(BUILDDIR) all install DESTDIR=$(PREFIX) >> $(LOGDIR)/newlib-$(ARCH).log

gcc-pass2: BUILDDIR=$(GCC_DIR)/build
gcc-pass2:
	@echo "+++ Building $(GCC_DIR) to $(BUILDDIR) (pass 2)..."
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && \
		$(GCC_DIR)/configure --target=$(TARGET) --prefix=$(PREFIX) \
		--with-newlib --enable-languages=$(LANGS) \
		--disable-libssp --disable-tls $(CONFIG_ARGS) \
		> $(LOGDIR)/gcc-pass2-$(ARCH).log
	make -C $(BUILDDIR) all install DESTDIR=$(PREFIX) >> $(LOGDIR)/gcc-pass2-$(ARCH).log


$(GCC_DIR): $(GCC_PKG)
	tar xf $(GCC_PKG)

$(BINUTILS_DIR): $(BINUTILS_PKG)
	tar xf $(BINUTILS_PKG)

$(NEWLIB_DIR): $(NEWLIB_PKG)
	tar xf $(NEWLIB_PKG)

$(GCC_PKG):
	wget http://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VER)/gcc-$(GCC_VER).tar.bz2

$(BINUTILS_PKG):
	wget http://ftp.gnu.org/gnu/binutils/binutils-$(BINUTILS_VER).tar.bz2

$(NEWLIB_PKG):
	wget ftp://sourceware.org/pub/newlib/newlib-$(NEWLIB_VER).tar.gz


.PHONY: clean

clean:
	rm -rf $(GCC_DIR)
	rm -rf $(BINUTILS_DIR)
	rm -rf $(NEWLIB_DIR)

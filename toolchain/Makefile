# == GCC Cross Compiler toolchain for Mega Drive and 32X ==
# Based on kubilus1's, which was in turn based on Chilly Willy's

# == Flag Explanations ==
# - For all targets
# enable-shared=no:      Disables dynamic linking -- static only
# disable-nls:           Native language support, not needed
# disable-werror:        Just who's idea was it for Werror to be the default?
# - For binutils
# enable-install-libbfd: Required for LTO to work
# - For GCC
# without-headers:       Leaves out the stdlib headers
# disable-libssp:        Library that requires stdlib causing failure
# disable-threads/tls:   MD programs are freestanding, so no thread model
# disable-multilib:      Only compiles m68000 support (no other m680x0)
# without-libstdcxx:     (C++) The STL is way too big for MD

# == Resuming in case of failure ==
# At the end of each successful step is a "touch" command to creat a marker file
# These files can be deleted to redo the step again, "clean" also deletes them

# == Newlib ==
# To include optional Newlib support, use the 'all-newlib' target
# make all-newlib ARCH=m68k
# Newlib provides a libc implementation for embedded systems
# However, we need the cross compiler to build it first
# Because of this GCC is built in 2 passes:
# The first pass builds C support only for building newlib
# The second pass builds everything now that newlib's libc is available

# == Additional Languages ==
# If you want to build support for languages other than C define "LANGS" like this:
# make ARCH=m68k LANGS=c,c++
# C is required, enabled by default and the most well supported
# C++ is not extensively tested but all non-STL features are expected to work
# Go support has been dropped as it requires a beefy runtime to do anything useful

GCC_VER      ?= 10.3.0
BINUTILS_VER ?= 2.36.1
NEWLIB_VER   ?= 1.20.0

GNU_MIRROR   ?= https://mirrors.tripadvisor.com/gnu

GCC_DIR       = gcc-$(GCC_VER)
BINUTILS_DIR  = binutils-$(BINUTILS_VER)
NEWLIB_DIR    = newlib-$(NEWLIB_VER)

GCC_PKG       = $(GCC_DIR).tar.gz
BINUTILS_PKG  = $(BINUTILS_DIR).tar.gz
NEWLIB_PKG    = $(NEWLIB_DIR).tar.gz

LDSCRIPTS = $(MARSDEV)/ldscripts

ifeq ($(ARCH),m68k)
	CPU_ARGS = --with-cpu=m68000
endif
ifeq ($(ARCH),sh)
	CPU_ARGS = --with-endian=big --with-cpu=m2
endif

TARGET  = $(ARCH)-elf
PREFIX  = $(MARSDEV)/$(TARGET)
PATH   := $(PREFIX)/bin:$(PATH)
LOGDIR := $(shell pwd)

.PHONY: all all-newlib clean

all: mk-binutils mk-gcc $(LDSCRIPTS)

all-newlib: LANGS ?= c
all-newlib: mk-binutils mk-gcc mk-newlib mk-gcc2 $(LDSCRIPTS)

mk-binutils: $(BINUTILS_DIR)
mk-binutils: BUILD_DIR=$(BINUTILS_DIR)/build
mk-binutils:
	@echo "+++ Building $(BINUTILS_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) $(CPU_ARGS) \
		--enable-install-libbfd --enable-shared=no --disable-nls --disable-werror \
		> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	@touch mk-binutils
	@rm -rf $(BUILD_DIR)

mk-gcc: $(GCC_DIR)
mk-gcc: BUILD_DIR=$(GCC_DIR)/build
mk-gcc:
	@echo "+++ Building $(GCC_DIR) for $(ARCH)..."
	cd $(GCC_DIR) && ./contrib/download_prerequisites \
		> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-languages=c $(CPU_ARGS) \
		--without-headers --disable-libssp \
		--disable-threads --disable-tls --disable-multilib \
		--enable-shared=no --disable-nls --disable-werror \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	@touch mk-gcc
	@rm -rf $(BUILD_DIR)

mk-newlib: $(NEWLIB_DIR)
mk-newlib: BUILD_DIR=$(NEWLIB_DIR)/build
mk-newlib:
	@echo "+++ Building $(NEWLIB_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) $(CPU_ARGS) \
		--disable-multilib --disable-nls --disable-werror \
		> $(LOGDIR)/newlib-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install \
		>> $(LOGDIR)/newlib-$(ARCH).log 2>&1
	@touch mk-newlib
	@rm -rf $(BUILD_DIR)

mk-gcc2: $(GCC_DIR)
mk-gcc2: BUILD_DIR=$(GCC_DIR)/build
mk-gcc2:
	@echo "+++ Building $(GCC_DIR) for $(ARCH) (Pass 2)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-languages=$(LANGS) $(CPU_ARGS) \
		--without-headers --with-newlib --disable-libssp \
		--disable-libstacktrace --disable-libstdcxx \
		--disable-threads --disable-tls --disable-multilib \
		--enable-shared=no --disable-nls --disable-werror \
		> $(LOGDIR)/gcc2-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/gcc2-$(ARCH).log 2>&1
	@touch mk-gcc2
	@rm -rf $(BUILD_DIR)

$(BINUTILS_DIR): $(BINUTILS_PKG)
	tar xf $(BINUTILS_PKG)

$(GCC_DIR): $(GCC_PKG)
	tar xf $(GCC_PKG)

$(NEWLIB_DIR): $(NEWLIB_PKG)
	tar xf $(NEWLIB_PKG)

$(BINUTILS_PKG):
	@curl -O $(GNU_MIRROR)/binutils/$(BINUTILS_PKG)

$(GCC_PKG):
	@curl -O $(GNU_MIRROR)/gcc/gcc-$(GCC_VER)/$(GCC_PKG)

$(NEWLIB_PKG):
	@curl -O ftp://sourceware.org/pub/newlib/$(NEWLIB_PKG)

$(LDSCRIPTS):
	cp -rf ldscripts/ $(LDSCRIPTS)

clean:
	rm -rf $(GCC_DIR)
	rm -rf $(BINUTILS_DIR)
	rm -rf $(NEWLIB_DIR)
	rm -f mk-binutils mk-gcc mk-newlib mk-gcc2

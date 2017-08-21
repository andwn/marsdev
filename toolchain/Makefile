GCC_VER      = 7.2.0
BINUTILS_VER = 2.29

GCC_DIR      = gcc-$(GCC_VER)
BINUTILS_DIR = binutils-$(BINUTILS_VER)

GCC_PKG      = $(GCC_DIR).tar.gz
BINUTILS_PKG = $(BINUTILS_DIR).tar.gz

TARGET  = $(ARCH)-elf
PREFIX  = $(MARSDEV)/$(TARGET)
PATH   := $(PREFIX)/bin:$(PATH)
LOGDIR := $(shell pwd)

ifeq ($(ARCH),m68k)
	CPU_ARGS = --with-cpu=m68000
	LANGS = c
endif
ifeq ($(ARCH),sh)
	CPU_ARGS = --with-endian=big --with-cpu=m2
	LANGS = c,c++
endif


.PHONY: all binutils gcc clean

all: $(BINUTILS_DIR) $(GCC_DIR) binutils gcc

binutils: BUILD_DIR=$(BINUTILS_DIR)/build
binutils:
	@echo "+++ Building $(BINUTILS_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) $(CPU_ARGS) \
		--enable-install-libbfd --disable-nls --disable-werror \
		> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	rm -rf $(BINUTILS_DIR)

gcc: BUILD_DIR=$(GCC_DIR)/build
gcc:
	@echo "+++ Building $(GCC_DIR) for $(ARCH)..."
	# Uncomment this line if you can't use ftp for whatever reason
	#sed -i 's/ftp:/http:/g' $(GCC_DIR)/contrib/download_prerequisites
	cd $(GCC_DIR) && ./contrib/download_prerequisites \
		> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--without-headers --enable-languages=$(LANGS) $(CPU_ARGS) \
		--disable-threads --disable-shared --disable-libssp \
		--disable-multilib --disable-tls --disable-nls --disable-werror \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	make -C $(BUILD_DIR) all install-strip \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	rm -rf $(GCC_DIR)

$(BINUTILS_DIR): $(BINUTILS_PKG)
	tar xf $(BINUTILS_PKG)

$(GCC_DIR): $(GCC_PKG)
	tar xf $(GCC_PKG)

$(BINUTILS_PKG):
	@wget https://mirrors.tripadvisor.com/gnu/binutils/$(BINUTILS_PKG)

$(GCC_PKG):
	@wget https://mirrors.tripadvisor.com/gnu/gcc/gcc-$(GCC_VER)/$(GCC_PKG)

clean:
	rm -rf $(GCC_DIR)
	rm -rf $(BINUTILS_DIR)

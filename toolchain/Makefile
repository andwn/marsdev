# == GCC Cross Compiler toolchain for Mega Drive and 32X ==
# Based on kubilus1's, which was in turn based on Chilly Willy's

# == Flag Explanations ==
# - For all targets
# enable-shared=no:        Disables dynamic linking -- static only
# enable-nls:              Enables the compiler to yell at you in your native language
# disable-werror:          Just who's idea was it for Werror to be the default?
# - For binutils
# enable-install-libbfd:   Required for LTO to work
# - For GCC
# without-headers:         Leaves out the stdlib headers
# disable-libssp:          Library that requires stdlib causing failure
# disable-threads/tls:     MD programs are freestanding, so no thread model
# disable-multilib:        Only compiles m68000 support (no other m680x0)
# disable-hosted-libstdxx: (C++) Only build the freestanding parts of libstdc++
# without-libstdcxx:       (C++) Disable libstdc++ entirely

# == Resuming in case of failure ==
# At the end of each successful step is a "touch" command to create a marker file.
# These files can be deleted to redo the step again, "clean" also deletes them.

# == Newlib ==
# To include optional Newlib support, use the 'all-newlib' target:
# make all-newlib ARCH=m68k
# Newlib provides a libc implementation for embedded systems.
# However, we need the cross compiler to build it first.
# Because of this, GCC is built in 2 passes:
# The first pass builds C support only for building newlib.
# The second pass builds everything now that newlib's libc is available.

# == Additional Languages ==
# If you want to build support for languages other than C define "LANGS" like this:
# make ARCH=m68k LANGS=c,c++
# C is required, enabled by default and the most well supported.
# C++ is not extensively tested but all non-STL features are expected to work.
# Go support has been dropped as it requires a beefy runtime to do anything useful.

# == Mars Mirror vs Public Mirrors ==
# I set up a VPS with all the required packages in a flat folder.
# SHA-256 sums are checked after downloading in case it gets dorobo'd.
# Pass USE_MARS_MIRROR=false to use the GNU/Sourceware public ones instead.
MARS_MIRROR     ?= https://tenshi.skychase.zone/
USE_MARS_MIRROR ?= true

GCC_VER      ?= 12.2.0
BINUTILS_VER ?= 2.39
NEWLIB_VER   ?= 4.2.0.20211231

GCC_DIR       = gcc-$(GCC_VER)
BINUTILS_DIR  = binutils-$(BINUTILS_VER)
NEWLIB_DIR    = newlib-$(NEWLIB_VER)

GCC_PKG       = $(GCC_DIR).tar.xz
BINUTILS_PKG  = $(BINUTILS_DIR).tar.xz
NEWLIB_PKG    = $(NEWLIB_DIR).tar.gz

GCC_SHA       = e549cf9cf3594a00e27b6589d4322d70e0720cdd213f39beb4181e06926230ff
BINUTILS_SHA  = 645c25f563b8adc0a81dbd6a41cffbf4d37083a382e02d5d3df4f65c09516d00
NEWLIB_SHA    = c3a0e8b63bc3bef1aeee4ca3906b53b3b86c8d139867607369cb2915ffc54435

# ISL, GMP, MPC, and MPFR are libraries required to compile GCC.
# When using the alternative mirrors, the contrib/download_prerequisites
# script provided by GCC is used to download them instead, in which case
# these version numbers and package names will not be used
ISL_VER       = 0.24
GMP_VER       = 6.2.1
MPC_VER       = 1.2.1
MPFR_VER      = 4.1.0

ISL_DIR       = isl-$(ISL_VER)
GMP_DIR       = gmp-$(GMP_VER)
MPC_DIR       = mpc-$(MPC_VER)
MPFR_DIR      = mpfr-$(MPFR_VER)

ISL_PKG       = $(ISL_DIR).tar.bz2
GMP_PKG       = $(GMP_DIR).tar.xz
MPC_PKG       = $(MPC_DIR).tar.gz
MPFR_PKG      = $(MPFR_DIR).tar.xz

ISL_SHA       = fcf78dd9656c10eb8cf9fbd5f59a0b6b01386205fe1934b3b287a0a1898145c0
GMP_SHA       = fd4829912cddd12f84181c3451cc752be224643e87fac497b69edddadc49b4f2
MPC_SHA       = 17503d2c395dfcf106b622dc142683c1199431d095367c6aacba6eec30340459
MPFR_SHA      = 0c98a3f1732ff6ca4ea690552079da9c597872d30e96ec28414ee23c95558a7f

LDSCRIPTS = $(MARSDEV)/ldscripts

ifeq ($(ARCH),m68k)
	CPU_ARGS = --with-cpu=m68000
endif
ifeq ($(ARCH),sh)
	CPU_ARGS = --with-endian=big --with-cpu=m2
endif

# Detect the number of processors for a parallel make
ifeq ($(shell uname),Darwin)
	NPROC := $(shell sysctl -n hw.logicalcpu)
else
	NPROC := $(shell nproc --all)
endif

TARGET  = $(ARCH)-elf
PREFIX  = $(MARSDEV)/$(TARGET)
PATH   := $(PREFIX)/bin:$(PATH)
LOGDIR := $(shell pwd)
LANGS  ?= c

.PHONY: all all-newlib clean

all: LANGS1P = $(LANGS)
all: mk-gcc-$(ARCH) $(LDSCRIPTS)

all-newlib: LANGS1P = c
all-newlib: mk-gcc2-$(ARCH) $(LDSCRIPTS)

mk-binutils-$(ARCH): $(BINUTILS_DIR)
mk-binutils-$(ARCH): BUILD_DIR=$(BINUTILS_DIR)/build-$(ARCH)
mk-binutils-$(ARCH):
	@echo "+++ Building $(BINUTILS_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--libdir=$(MARSDEV)/$(TARGET)/lib --libexecdir=$(MARSDEV)/$(TARGET)/libexec \
		$(CPU_ARGS) \
		--enable-install-libbfd --enable-shared=no --disable-werror \
		> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) all -j$(NPROC) \
		>> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) install-strip \
		>> $(LOGDIR)/binutils-$(ARCH).log 2>&1
	@touch mk-binutils-$(ARCH)
	@rm -rf $(BUILD_DIR)

mk-gcc-$(ARCH): $(GCC_DIR) mk-binutils-$(ARCH)
mk-gcc-$(ARCH): BUILD_DIR=$(GCC_DIR)/build-gcc1-$(ARCH)
mk-gcc-$(ARCH): 
	@echo "+++ Building $(GCC_DIR) for $(ARCH)..."
	if [ ! $(USE_MARS_MIRROR) ]; then \
		cd $(GCC_DIR) && ./contrib/download_prerequisites \
			> $(LOGDIR)/gcc-$(ARCH).log 2>&1 ; \
	fi
	#-patch -p0 < libcc1_suse_fix.patch
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--libdir=$(MARSDEV)/$(TARGET)/lib --libexecdir=$(MARSDEV)/$(TARGET)/libexec \
		--enable-languages=$(LANGS1P) $(CPU_ARGS) \
		--without-headers --disable-libssp --disable-threads --disable-tls \
		--disable-multilib --enable-shared=no --disable-werror \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) all -j$(NPROC) \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) install-strip \
		>> $(LOGDIR)/gcc-$(ARCH).log 2>&1
	@touch mk-gcc-$(ARCH)
	@rm -rf $(BUILD_DIR)

mk-newlib-$(ARCH): $(NEWLIB_DIR) mk-gcc-$(ARCH)
mk-newlib-$(ARCH): BUILD_DIR=$(NEWLIB_DIR)/build-$(ARCH)
mk-newlib-$(ARCH): 
	@echo "+++ Building $(NEWLIB_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--libdir=$(MARSDEV)/$(TARGET)/lib --libexecdir=$(MARSDEV)/$(TARGET)/libexec \
		$(CPU_ARGS) --disable-multilib --disable-werror \
		> $(LOGDIR)/newlib-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) all -j$(NPROC) \
		>> $(LOGDIR)/newlib-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) install \
		>> $(LOGDIR)/newlib-$(ARCH).log 2>&1
	@touch mk-newlib-$(ARCH)
	@rm -rf $(BUILD_DIR)

mk-gcc2-$(ARCH): $(GCC_DIR) mk-newlib-$(ARCH)
mk-gcc2-$(ARCH): BUILD_DIR=$(GCC_DIR)/build-gcc2-$(ARCH)
mk-gcc2-$(ARCH): 
	@echo "+++ Building $(GCC_DIR) for $(ARCH) (Pass 2)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
	   	--libdir=$(MARSDEV)/$(TARGET)/lib --libexecdir=$(MARSDEV)/$(TARGET)/libexec \
		--enable-languages=$(LANGS) $(CPU_ARGS) \
		--without-headers --with-newlib --disable-hosted-libstdxx \
		--disable-libssp --disable-threads --disable-tls \
		--disable-multilib --enable-shared=no --disable-werror \
		> $(LOGDIR)/gcc2-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) all -j$(NPROC) \
		>> $(LOGDIR)/gcc2-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) install-strip \
		>> $(LOGDIR)/gcc2-$(ARCH).log 2>&1
	@touch mk-gcc2-$(ARCH)
	@rm -rf $(BUILD_DIR)

$(BINUTILS_DIR): $(BINUTILS_PKG)
	tar xf $(BINUTILS_PKG)

$(GCC_DIR): $(GCC_PKG)
	tar xf $(GCC_PKG)
	if [ $(USE_MARS_MIRROR) ]; then \
		tar xf $(ISL_PKG) -C $(GCC_DIR) && mv $(GCC_DIR)/$(ISL_DIR) $(GCC_DIR)/isl ; \
		tar xf $(GMP_PKG) -C $(GCC_DIR) && mv $(GCC_DIR)/$(GMP_DIR) $(GCC_DIR)/gmp ; \
		tar xf $(MPC_PKG) -C $(GCC_DIR) && mv $(GCC_DIR)/$(MPC_DIR) $(GCC_DIR)/mpc ; \
		tar xf $(MPFR_PKG) -C $(GCC_DIR) && mv $(GCC_DIR)/$(MPFR_DIR) $(GCC_DIR)/mpfr ; \
	fi

$(NEWLIB_DIR): $(NEWLIB_PKG)
	tar xf $(NEWLIB_PKG)

$(BINUTILS_PKG):
	@if [ ! $(USE_MARS_MIRROR) ]; then \
		wget https://ftp.gnu.org/gnu/binutils/$(BINUTILS_PKG) ; \
	else \
		wget $(MARS_MIRROR)$(BINUTILS_PKG) ; \
	fi
	@echo "$(BINUTILS_SHA) $(BINUTILS_PKG)" | sha256sum -c

$(GCC_PKG):
	@if [ ! $(USE_MARS_MIRROR) ]; then \
		wget https://ftp.gnu.org/gnu/gcc/gcc-$(GCC_VER)/$(GCC_PKG) ; \
		echo "$(GCC_SHA) $(GCC_PKG)" | sha256sum -c ; \
	else \
		wget $(MARS_MIRROR)$(GCC_PKG) ; \
		echo "$(GCC_SHA) $(GCC_PKG)" | sha256sum -c ; \
		wget $(MARS_MIRROR)$(ISL_PKG) ; \
		echo "$(ISL_SHA) $(ISL_PKG)" | sha256sum -c ; \
		wget $(MARS_MIRROR)$(GMP_PKG) ; \
		echo "$(GMP_SHA) $(GMP_PKG)" | sha256sum -c ; \
		wget $(MARS_MIRROR)$(MPC_PKG) ; \
		echo "$(MPC_SHA) $(MPC_PKG)" | sha256sum -c ; \
		wget $(MARS_MIRROR)$(MPFR_PKG) ; \
		echo "$(MPFR_SHA) $(MPFR_PKG)" | sha256sum -c ; \
	fi

$(NEWLIB_PKG):
	@if [ ! $(USE_MARS_MIRROR) ]; then \
		wget ftp://sourceware.org/pub/newlib/$(NEWLIB_PKG) ; \
	else \
		wget $(MARS_MIRROR)$(NEWLIB_PKG) ; \
	fi
	@echo "$(NEWLIB_SHA) $(NEWLIB_PKG)" | sha256sum -c

$(LDSCRIPTS):
	cp -rf ldscripts/ $(LDSCRIPTS)

clean:
	rm -rf $(GCC_DIR)
	rm -rf $(BINUTILS_DIR)
	rm -rf $(NEWLIB_DIR)
	rm -f mk-binutils-* mk-gcc-* mk-newlib-* mk-gcc2-*

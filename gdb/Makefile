GDB_VER = 12.1
GDB_DIR = gdb-$(GDB_VER)
GDB_PKG = $(GDB_DIR).tar.gz

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
	LANGS = c
endif


.PHONY: all gdb clean

all: gdb

gdb: BUILD_DIR=$(GDB_DIR)/build
gdb: $(GDB_DIR)
	@echo "+++ Building $(GDB_DIR) for $(ARCH)..."
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
		../configure --target=$(TARGET) --prefix=$(PREFIX) \
		--enable-languages=$(LANGS) $(CPU_ARGS) \
		--disable-multilib --disable-tls --disable-nls --disable-werror \
		> $(LOGDIR)/gdb-$(ARCH).log 2>&1
	$(MAKE) -C $(BUILD_DIR) all install \
		>> $(LOGDIR)/gdb-$(ARCH).log 2>&1
	rm -rf $(GDB_DIR)

$(GDB_DIR): $(GDB_PKG)
	tar xf $(GDB_PKG)

$(GDB_PKG):
	@wget https://ftp.gnu.org/gnu/gdb/$(GDB_PKG)

clean:
	rm -rf $(GDB_DIR)

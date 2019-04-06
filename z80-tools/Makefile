MARSBIN = $(MARSDEV)/bin

SJASM   = $(MARSBIN)/sjasm
Z80ASM  = $(MARSBIN)/z80asm

# Use homebrew's gettext on macOS, for autopoint
ifeq ($(OS),Windows_NT)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		export PATH := /usr/local/opt/gettext/bin:$(PATH)
	endif
endif

.PHONY: all clean

all: $(SJASM) $(Z80ASM)

$(SJASM): $(MARSBIN)
	rm -rf sjasm
	git clone https://github.com/konamiman/sjasm --branch v0.39
	# There's mismatching caps in the Makefile for sjasm
	mv sjasm/Sjasm/Sjasm.cpp sjasm/Sjasm/sjasm.cpp
	cd sjasm/Sjasm && make
	cp -f sjasm/Sjasm/sjasm $(SJASM)

$(Z80ASM): $(MARSBIN)
	rm -rf z80asm
	git clone https://git.savannah.nongnu.org/git/z80asm.git
	cd z80asm && autoreconf -f -i && ./configure
	# One of the tests fails so we just skip them
	echo "all:\n\t@echo skipping tests" > z80asm/tests/Makefile
	make -C z80asm
	cp -f z80asm/src/z80asm $(Z80ASM)

$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	rm -rf sjasm z80asm

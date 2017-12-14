MARSBIN = $(MARSDEV)/bin

SJASM   = $(MARSBIN)/sjasm
Z80ASM  = $(MARSBIN)/z80asm

.PHONY: all clean

all: $(SJASM)
#$(Z80ASM)

$(SJASM): $(MARSBIN)
	rm -rf sjasm
	git clone https://github.com/konamiman/sjasm --branch v0.39
	# Are you fucking kidding me
	mv sjasm/Sjasm/Sjasm.cpp sjasm/Sjasm/sjasm.cpp
	cd sjasm/Sjasm && make -f ../Makefile
	cp -f sjasm/Sjasm/sjasm $(SJASM)

$(Z80ASM): $(MARSBIN)
	rm -rf z80asm
	git clone https://git.savannah.nongnu.org/git/z80asm.git
	cd z80asm && autoreconf -f -i && ./configure && make
	cp -f z80asm/src/z80asm $(Z80ASM)

$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	rm -rf sjasm z80asm

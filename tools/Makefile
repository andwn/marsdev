SJASM = $(MARSDEV)/bin/sjasm
Z80ASM = $(MARSDEV)/bin/z80asm

MDTILER = $(MARSDEV)/bin/mdtiler
SLZ     = $(MARSDEV)/bin/slz
UFTC    = $(MARSDEV)/bin/uftc
MML2ESF = $(MARSDEV)/bin/mml2esf
PCM2EWF = $(MARSDEV)/bin/pcm2ewf
TFI2EIF = $(MARSDEV)/bin/tfi2eif

.PHONY: all z80 mdt clean

all: $(MARSDEV)/bin z80 mdt

z80: $(SJASM) $(Z80ASM)

mdt: mdtools $(MDTILER) $(SLZ) $(UFTC) $(MML2ESF) $(PCM2EWF) $(TFI2EIF)

$(MARSDEV)/bin:
	mkdir -p $(MARSDEV)/bin

# Z80 Assemblers

$(SJASM): 
	rm -rf sjasm
	git clone https://github.com/konamiman/sjasm --branch v0.39 --single-branch
	# Are you fucking kidding me
	mv sjasm/Sjasm/Sjasm.cpp sjasm/Sjasm/sjasm.cpp
	cd sjasm/Sjasm && make -f ../Makefile
	cp -f sjasm/Sjasm/sjasm $(SJASM)

$(Z80ASM):
	rm -rf z80asm
	git clone https://git.savannah.nongnu.org/git/z80asm.git
	cd z80asm && autoreconf -f -i && ./configure && make
	cp -f z80asm/src/z80asm $(Z80ASM)

# mdtools

mdtools:
	git clone https://github.com/sikthehedgehog/mdtools

$(MDTILER):
	make -C mdtools/mdtiler/tool
	cp -f mdtools/mdtiler/tool/mdtiler $(MDTILER)

$(SLZ):
	make -C mdtools/slz/tool
	cp -f mdtools/slz/tool/slz $(SLZ)

$(UFTC):
	make -C mdtools/uftc/tool
	cp -f mdtools/uftc/tool/uftc $(UFTC)

$(MML2ESF):
	make -C mdtools/mml2esf/tool
	cp -f mdtools/mml2esf/tool/mml2esf $(MML2ESF)

$(PCM2EWF):
	make -C mdtools/pcm2ewf/tool
	cp -f mdtools/pcm2ewf/tool/pcm2ewf $(PCM2EWF)

$(TFI2EIF):
	make -C mdtools/tfi2eif/tool
	cp -f mdtools/tfi2eif/tool/tfi2eif $(TFI2EIF)


clean:
	rm -rf sjasm z80asm mdtools

MARSBIN = $(MARSDEV)/bin

SJASM   = $(MARSBIN)/sjasm
Z80ASM  = $(MARSBIN)/z80asm

MDTILER = $(MARSBIN)/mdtiler
SLZ     = $(MARSBIN)/slz
UFTC    = $(MARSBIN)/uftc
MML2ESF = $(MARSBIN)/mml2esf
PCM2EWF = $(MARSBIN)/pcm2ewf
TFI2EIF = $(MARSBIN)/tfi2eif

LDSCRIPTS = $(MARSDEV)/ldscripts

.PHONY: all mdtools-build clean

all: $(MARSBIN) $(Z80ASM) $(LDSCRIPTS) mdtools-build

mdtools-build: $(MDTILER) $(SLZ) $(UFTC) $(MML2ESF) $(PCM2EWF) $(TFI2EIF)

$(MARSBIN):
	mkdir -p $(MARSBIN)

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

$(MDTILER): mdtools
	make -C mdtools/mdtiler/tool
	cp -f mdtools/mdtiler/tool/mdtiler $(MDTILER)

$(SLZ): mdtools
	make -C mdtools/slz/tool
	cp -f mdtools/slz/tool/slz $(SLZ)

$(UFTC): mdtools
	make -C mdtools/uftc/tool
	cp -f mdtools/uftc/tool/uftc $(UFTC)

$(MML2ESF): mdtools
	make -C mdtools/mml2esf/tool
	cp -f mdtools/mml2esf/tool/mml2esf $(MML2ESF)

$(PCM2EWF): mdtools
	make -C mdtools/pcm2ewf/tool
	cp -f mdtools/pcm2ewf/tool/pcm2ewf $(PCM2EWF)

$(TFI2EIF): mdtools
	make -C mdtools/tfi2eif/tool
	cp -f mdtools/tfi2eif/tool/tfi2eif $(TFI2EIF)

# ldfiles

$(LDSCRIPTS):
	cp -rf ldscripts/ $(LDSCRIPTS)


clean:
	rm -rf sjasm z80asm mdtools

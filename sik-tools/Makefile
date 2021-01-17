MARSBIN = $(MARSDEV)/bin

MDTILER  = $(MARSBIN)/mdtiler
MIDI2ESF = $(MARSBIN)/midi2esf
MML2ESF  = $(MARSBIN)/mml2esf
TFI2EIF  = $(MARSBIN)/tfi2eif
VGI2EIF  = $(MARSBIN)/vgi2eif
EIF2TFI  = $(MARSBIN)/eif2tfi
PCM2EWF  = $(MARSBIN)/pcm2ewf
ECHO2VGM = $(MARSBIN)/echo2vgm
SLZ      = $(MARSBIN)/slz
UFTC     = $(MARSBIN)/uftc
HEADGEN  = $(MARSBIN)/headgen
ROMFIX   = $(MARSBIN)/romfix

.PHONY: all clean

all: $(MDTILER)
all: $(MIDI2ESF) $(MML2ESF) $(TFI2EIF) $(VGI2EIF) $(EIF2TFI) $(PCM2EWF) $(ECHO2VGM)
all: $(SLZ) $(UFTC)
all: $(HEADGEN) $(ROMFIX)

mdtools:
	git clone https://github.com/sikthehedgehog/mdtools
	#git clone https://github.com/andwn/mdtools

$(MDTILER): mdtools $(MARSBIN)
	make -C mdtools/mdtiler/tool
	cp -f mdtools/mdtiler/tool/mdtiler $(MDTILER)

$(MIDI2ESF): mdtools $(MARSBIN)
	make -C mdtools/midi2esf
	cp -f mdtools/midi2esf/midi2esf $(MIDI2ESF)

$(MML2ESF): mdtools $(MARSBIN)
	make -C mdtools/mml2esf/tool
	cp -f mdtools/mml2esf/tool/mml2esf $(MML2ESF)

$(TFI2EIF): mdtools $(MARSBIN)
	make -C mdtools/tfi2eif/tool
	cp -f mdtools/tfi2eif/tool/tfi2eif $(TFI2EIF)

$(VGI2EIF): mdtools $(MARSBIN)
	make -C mdtools/vgi2eif/tool
	cp -f mdtools/vgi2eif/tool/vgi2eif $(VGI2EIF)

$(EIF2TFI): mdtools $(MARSBIN)
	make -C mdtools/eif2tfi/tool
	cp -f mdtools/eif2tfi/tool/eif2tfi $(EIF2TFI)

$(PCM2EWF): mdtools $(MARSBIN)
	make -C mdtools/pcm2ewf/tool
	cp -f mdtools/pcm2ewf/tool/pcm2ewf $(PCM2EWF)

$(ECHO2VGM): mdtools $(MARSBIN)
	# echo2vgm fails to compile in Windows
	if [ $(OS) != Windows_NT ]; then \
		make -C mdtools/echo2vgm; \
		cp -f mdtools/echo2vgm/echo2vgm $(ECHO2VGM); \
	fi

$(SLZ): mdtools $(MARSBIN)
	make -C mdtools/slz/tool
	cp -f mdtools/slz/tool/slz $(SLZ)

$(UFTC): mdtools $(MARSBIN)
	make -C mdtools/uftc/tool
	cp -f mdtools/uftc/tool/uftc $(UFTC)

$(HEADGEN): mdtools $(MARSBIN)
	make -C mdtools/headgen/tool
	cp -f mdtools/headgen/tool/headgen $(HEADGEN)

$(ROMFIX): mdtools $(MARSBIN)
	make -C mdtools/romfix
	cp -f mdtools/romfix/romfix $(ROMFIX)
 
$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	rm -rf mdtools

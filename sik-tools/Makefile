MARSBIN = $(MARSDEV)/bin

HEADGEN = $(MARSBIN)/headgen
MDTILER = $(MARSBIN)/mdtiler
MIDI2ESF= $(MARSBIN)/midi2esf
MML2ESF = $(MARSBIN)/mml2esf
TFI2EIF = $(MARSBIN)/tfi2eif
VGI2EIF = $(MARSBIN)/vgi2eif
PCM2EWF = $(MARSBIN)/pcm2ewf
SLZ     = $(MARSBIN)/slz
UFTC    = $(MARSBIN)/uftc

.PHONY: all clean

all: $(HEADGEN) $(MDTILER) $(SLZ) $(UFTC)
all: $(MML2ESF) $(TFI2EIF) $(VGI2EIF) $(PCM2EWF)

mdtools:
	#git clone https://github.com/sikthehedgehog/mdtools
	git clone https://github.com/andwn/mdtools

$(HEADGEN): mdtools $(MARSBIN)
	make -C mdtools/headgen/tool
	cp -f mdtools/headgen/tool/headgen $(HEADGEN)

$(MDTILER): mdtools $(MARSBIN)
	make -C mdtools/mdtiler/tool
	cp -f mdtools/mdtiler/tool/mdtiler $(MDTILER)

$(MIDI2ESF): mdtools $(MARSBIN)
	make -C mdtools/midi2esf
	cp -f mdtools/midi2esf/midi2esf $(MIDI2ESF)

$(MML2ESF): mdtools $(MARSBIN)
	make -C mdtools/mml2esf/tool
	cp -f mdtools/mml2esf/tool/mml2esf $(MML2ESF)

$(PCM2EWF): mdtools $(MARSBIN)
	make -C mdtools/pcm2ewf/tool
	cp -f mdtools/pcm2ewf/tool/pcm2ewf $(PCM2EWF)

$(TFI2EIF): mdtools $(MARSBIN)
	make -C mdtools/tfi2eif/tool
	cp -f mdtools/tfi2eif/tool/tfi2eif $(TFI2EIF)

$(VGI2EIF): mdtools $(MARSBIN)
	make -C mdtools/vgi2eif/tool
	cp -f mdtools/vgi2eif/tool/vgi2eif $(VGI2EIF)

$(SLZ): mdtools $(MARSBIN)
	make -C mdtools/slz/tool
	cp -f mdtools/slz/tool/slz $(SLZ)

$(UFTC): mdtools $(MARSBIN)
	make -C mdtools/uftc/tool
	cp -f mdtools/uftc/tool/uftc $(UFTC)
 
$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	rm -rf mdtools

MARSBIN = $(MARSDEV)/bin

MDTILER = $(MARSBIN)/mdtiler
SLZ     = $(MARSBIN)/slz
UFTC    = $(MARSBIN)/uftc
MML2ESF = $(MARSBIN)/mml2esf
PCM2EWF = $(MARSBIN)/pcm2ewf
TFI2EIF = $(MARSBIN)/tfi2eif

.PHONY: all clean

all: $(MDTILER) $(SLZ) $(UFTC) $(MML2ESF) $(PCM2EWF) $(TFI2EIF)

mdtools:
	git clone https://github.com/sikthehedgehog/mdtools

$(MDTILER): mdtools $(MARSBIN)
	make -C mdtools/mdtiler/tool
	cp -f mdtools/mdtiler/tool/mdtiler $(MDTILER)

$(SLZ): mdtools $(MARSBIN)
	make -C mdtools/slz/tool
	cp -f mdtools/slz/tool/slz $(SLZ)

$(UFTC): mdtools $(MARSBIN)
	make -C mdtools/uftc/tool
	cp -f mdtools/uftc/tool/uftc $(UFTC)
 
$(MML2ESF): mdtools $(MARSBIN)
	make -C mdtools/mml2esf/tool
	cp -f mdtools/mml2esf/tool/mml2esf $(MML2ESF)

$(PCM2EWF): mdtools $(MARSBIN)
	make -C mdtools/pcm2ewf/tool
	cp -f mdtools/pcm2ewf/tool/pcm2ewf $(PCM2EWF)

$(TFI2EIF): mdtools $(MARSBIN)
	make -C mdtools/tfi2eif/tool
	cp -f mdtools/tfi2eif/tool/tfi2eif $(TFI2EIF)

$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	rm -rf mdtools

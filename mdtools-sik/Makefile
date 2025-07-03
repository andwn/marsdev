ifeq ($(shell which ldconfig),)
else
ifeq ($(shell /sbin/ldconfig -p | grep libpng),)
  $(error "'libpng' not found. Make sure the 'libpng-dev' package is installed.")
endif
endif

MARSDEV = $(MARS_BUILD_DIR)
MARSBIN = $(MARSDEV)/m68k-elf/bin

MDTILERMOD  = $(MARSBIN)/mdtilermod

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

all: $(MDTILERMOD) $(MDTILER)
all: $(MIDI2ESF) $(MML2ESF) $(TFI2EIF) $(VGI2EIF) $(EIF2TFI) $(PCM2EWF) $(ECHO2VGM)
all: $(SLZ) $(UFTC)
all: $(HEADGEN) $(ROMFIX)

mdtiler-mod:
	git submodule update --init

mdtools:
	git submodule update --init

$(MDTILERMOD): mdtiler-mod $(MARSBIN)
	$(MAKE) -C mdtiler-mod
	cp -f mdtiler-mod/mdtiler $(MDTILERMOD)

$(MDTILER): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/mdtiler/tool
	cp -f mdtools/mdtiler/tool/mdtiler $(MDTILER)

$(MIDI2ESF): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/midi2esf
	cp -f mdtools/midi2esf/midi2esf $(MIDI2ESF)

$(MML2ESF): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/mml2esf/tool
	cp -f mdtools/mml2esf/tool/mml2esf $(MML2ESF)

$(TFI2EIF): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/tfi2eif/tool
	cp -f mdtools/tfi2eif/tool/tfi2eif $(TFI2EIF)

$(VGI2EIF): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/vgi2eif/tool
	cp -f mdtools/vgi2eif/tool/vgi2eif $(VGI2EIF)

$(EIF2TFI): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/eif2tfi/tool
	cp -f mdtools/eif2tfi/tool/eif2tfi $(EIF2TFI)

$(PCM2EWF): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/pcm2ewf/tool
	cp -f mdtools/pcm2ewf/tool/pcm2ewf $(PCM2EWF)

$(ECHO2VGM): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/echo2vgm
	cp -f mdtools/echo2vgm/echo2vgm $(ECHO2VGM)

$(SLZ): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/slz/tool
	cp -f mdtools/slz/tool/slz $(SLZ)

$(UFTC): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/uftc/tool
	cp -f mdtools/uftc/tool/uftc $(UFTC)

$(HEADGEN): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/headgen/tool
	cp -f mdtools/headgen/tool/headgen $(HEADGEN)

$(ROMFIX): mdtools $(MARSBIN)
	$(MAKE) -C mdtools/romfix
	cp -f mdtools/romfix/romfix $(ROMFIX)

$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	$(MAKE) -C mdtiler-mod clean
	$(MAKE) -C mdtools/mdtiler/tool clean
	$(MAKE) -C mdtools/midi2esf clean
	$(MAKE) -C mdtools/mml2esf/tool clean
	$(MAKE) -C mdtools/tfi2eif/tool clean
	$(MAKE) -C mdtools/vgi2eif/tool clean
	$(MAKE) -C mdtools/eif2tfi/tool clean
	$(MAKE) -C mdtools/pcm2ewf/tool clean
	$(MAKE) -C mdtools/echo2vgm clean
	$(MAKE) -C mdtools/slz/tool clean
	$(MAKE) -C mdtools/uftc/tool clean
	$(MAKE) -C mdtools/headgen/tool clean
	$(MAKE) -C mdtools/romfix clean

# Makefile to build Flamewing's mdcomp and mdtools without
# being forced to install libraries globally to /usr/lib.
# I could not figure out how to do so with the CMake project.
#
# This way is rather dirty though, since it brute forces a
# glob of src/lib in the module list for every executable.
# But it works, and that's the important part.

MARSDEV = $(MARS_BUILD_DIR)
MARSBIN = $(MARSDEV)/m68k-elf/bin

# mdcomp tools
COMPCMP = $(MARSBIN)/compcmp
COMPERX = $(MARSBIN)/comperx
ENICMP  = $(MARSBIN)/enicmp
KOSCMP  = $(MARSBIN)/koscmp
KOSPLUS = $(MARSBIN)/kosplus
LZKN1CMP= $(MARSBIN)/lzkn1cmp
NEMCMP  = $(MARSBIN)/nemcmp
ROCKCMP = $(MARSBIN)/rockcmp
SAXCMP  = $(MARSBIN)/saxcmp
SNKCMP  = $(MARSBIN)/snkcmp

# mdtools tools
VOICEDUMPER = $(MARSBIN)/voice_dumper
CHUNKCENSUS = $(MARSBIN)/chunk_census
SPLITART    = $(MARSBIN)/split_art
CHUNKSPLIT  = $(MARSBIN)/chunk_splitter
SSEXPAND    = $(MARSBIN)/ssexpand
SMPS2ASM    = $(MARSBIN)/smps2asm
RECOLORART  = $(MARSBIN)/recolor_art
MAPPINGTOOL = $(MARSBIN)/mapping_tool
PLANEMAP    = $(MARSBIN)/plane_map
ENITOOL     = $(MARSBIN)/enitool

COMP_INCS  = -Imdcomp/include
COMP_DEPS  = mdcomp/src/lib/*.cc

TOOL_INCS  = $(COMP_INCS) -Ifmt/include -Imdtools/include
TOOL_DEPS  = -std=c++20 $(COMP_DEPS) fmt/src/format.cc mdtools/src/lib/*.cc
TOOL_DEPS += mdtools/src/tools/songtrack.cc mdtools/src/tools/fmvoice.cc

.PHONY: all comp tools clean

all: comp tools

comp: $(COMPCMP) $(COMPERX) $(ENICMP) $(KOSCMP) $(KOSPLUS)
comp: $(LZKN1CMP) $(NEMCMP) $(ROCKCMP) $(SAXCMP) $(SNKCMP)

tools: $(VOICEDUMPER) $(CHUNKCENSUS) $(SPLITART) $(CHUNKSPLIT)
tools: $(SSEXPAND) $(SMPS2ASM) $(RECOLORART) $(MAPPINGTOOL)
tools: $(PLANEMAP) $(ENITOOL)

# COMPRESSION TOOLS

$(COMPCMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/compcmp.cc -o $@
$(COMPERX): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/comperx.cc -o $@
$(ENICMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/enicmp.cc -o $@
$(KOSCMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/koscmp.cc -o $@
$(KOSPLUS): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/kosplus.cc -o $@
$(LZKN1CMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/lzkn1cmp.cc -o $@
$(NEMCMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/nemcmp.cc -o $@
$(ROCKCMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/rockcmp.cc -o $@
$(SAXCMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/saxcmp.cc -o $@
$(SNKCMP): | mdcomp $(MARSBIN)
	c++ $(COMP_INCS) $(COMP_DEPS) mdcomp/src/tools/snkcmp.cc -o $@

# MD TOOLS

$(VOICEDUMPER): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/voice_dumper.cc -o $@
$(CHUNKCENSUS): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/chunk_census.cc -o $@
$(SPLITART): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/split_art.cc -o $@
$(CHUNKSPLIT): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/chunk_splitter.cc -o $@
$(SSEXPAND): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/ssexpand.cc -o $@
$(SMPS2ASM): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/smps2asm.cc -o $@
$(RECOLORART): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/recolor_art.cc -o $@
$(MAPPINGTOOL): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/mapping_tool.cc -o $@
$(PLANEMAP): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/plane_map.cc -o $@
$(ENITOOL): | fmt mdtools $(MARSBIN)
	c++ $(TOOL_INCS) $(TOOL_DEPS) mdtools/src/tools/enitool.cc -o $@

# REPOSITORIES

mdcomp:
	git submodule update --init

fmt:
	git submodule update --init

mdtools:
	git submodule update --init

# DIRECTORIES

$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	

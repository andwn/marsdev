TOOLSBIN = $(MARSDEV)/bin

SJASM   = $(TOOLSBIN)/sjasm
SJBRANCH = v0.39

.PHONY: all clean

all: $(SJASM)

$(SJASM): $(TOOLSBIN)
	rm -rf sjasm
	git clone https://github.com/konamiman/sjasm --branch $(SJBRANCH)
	cd sjasm/Sjasm && make
	cp -f sjasm/Sjasm/sjasm $(SJASM)

$(TOOLSBIN):
	mkdir -p $(TOOLSBIN)

clean:
	rm -rf sjasm

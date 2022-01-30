MARSBIN = $(MARSDEV)/bin
MARSINC = $(MARSDEV)/include
MARSLIB = $(MARSDEV)/lib

GENERATOR = "Unix Makefiles"
MACFIX = true

ifeq ($(OS),Windows_NT)
	GENERATOR = "MSYS Makefiles"
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		MACFIX = ln -s /usr/local/include/boost include/boost
	endif
endif

all: clean $(MARSINC) $(MARSLIB)
	git clone --recurse-submodules https://github.com/flamewing/mdtools
	cd mdtools/mdcomp && $(MACFIX) \
		&& cmake -S . -B build -G $(GENERATOR) \
			-DCMAKE_INSTALL_PREFIX="$(MARSDEV)" \
		&& cmake --build build -j2 \
		&& cmake --install build
	cd mdtools && $(MACFIX) \
		&& cmake -S . -B build -G $(GENERATOR) \
			-DCMAKE_INSTALL_PREFIX="$(MARSDEV)" \
		&& cmake --build build -j2 \
		&& cmake --install build

$(MARSBIN):
	mkdir -p $(MARSBIN)

$(MARSINC):
	mkdir -p $(MARSINC)
	
$(MARSLIB):
	mkdir -p $(MARSLIB)
	
clean:
	rm -rf mdtools


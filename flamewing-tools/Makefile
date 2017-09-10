MARSBIN = $(MARSDEV)/bin
MARSINC = $(MARSDEV)/include
MARSLIB = $(MARSDEV)/lib

all: clean $(MARSINC) $(MARSLIB)
	# mdtools depends on mdcomp, install that first
	git clone https://github.com/flamewing/mdcomp
	cd mdcomp && ./autogen.sh "--prefix=$(MARSDEV)" \
			  && make install
	git clone https://github.com/flamewing/mdtools
	cd mdtools && ./autogen.sh "--prefix=$(MARSDEV)" \
				  "CPPFLAGS=-I$(MARSINC) -L$(MARSLIB)" "LDFLAGS=-L$(MARSLIB)" \
			   && make install

$(MARSBIN):
	mkdir -p $(MARSBIN)

$(MARSINC):
	mkdir -p $(MARSINC)
	
$(MARSLIB):
	mkdir -p $(MARSLIB)
	
clean:
	rm -rf mdtools
	rm -rf mdcomp

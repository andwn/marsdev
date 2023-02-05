export MARSDEV = $(MARS_BUILD_DIR)
MARSBIN = $(MARSDEV)/m68k-elf/bin
MARSLIB = $(MARSDEV)/m68k-elf/lib

all:
	rm -rf libdos-gcc
	git clone https://github.com/andwn/libdos-gcc
	make -C libdos-gcc
	cp -f libdos-gcc/libdos.a $(MARSLIB)/
	cp -f libdos-gcc/elf2x.py $(MARSBIN)/

clean:
	rm -rf libdos-gcc

MARSDEV = $(MARS_BUILD_DIR)
MARSBIN = $(MARSDEV)/m68k-elf/bin
MARSINC = $(MARSDEV)/m68k-elf/include
MARSLIB = $(MARSDEV)/m68k-elf/lib

LIBDOS   = $(MARSLIB)/libdos.a
PNG2XSP  = $(MARSBIN)/png2xsp

.PHONY: all clean

all: $(LIBDOS) $(PNG2XSP)

libdos-gcc:
	git submodule update --init

png2xsp:
	git submodule update --init

$(LIBDOS): libdos-gcc $(MARSBIN)
	$(MAKE) -C libdos-gcc
	cp -f libdos-gcc/libdos.a $(LIBDOS)

$(PNG2XSP): png2xsp $(MARSBIN)
	$(MAKE) -C png2xsp
	cp -f png2xsp/png2xsp $(PNG2XSP)

$(MARSBIN):
	mkdir -p $(MARSBIN)

clean:
	$(MAKE) -C libdos-gcc clean
	$(MAKE) -C png2xsp clean

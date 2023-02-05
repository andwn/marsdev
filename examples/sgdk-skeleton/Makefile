MARSDEV ?= /opt/toolchains/mars
export GDK  := $(MARSDEV)/m68k-elf
export PATH := $(GDK)/bin:$(PATH)

all:
	make -f $(GDK)/makefile.gen

clean:
	make -f $(GDK)/makefile.gen clean

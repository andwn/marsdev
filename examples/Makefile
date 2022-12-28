SUBDIRS=$(shell ls -d */)

all:
	$(foreach d, $(SUBDIRS), make -C $(d) &&) true

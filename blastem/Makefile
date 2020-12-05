BLASTEM_BITS = 64
BLASTEM_VER  = 0.6.2
BLASTEM_DIR  = blastem$(BLASTEM_BITS)-$(BLASTEM_VER)
BLASTEM_PKG  = $(BLASTEM_DIR).tar.gz

.PHONY: all blastem clean

all: blastem

blastem: $(BLASTEM_DIR)
	@echo "+++ Copying $(BLASTEM_DIR)..."
	cp -f -r $(BLASTEM_DIR) $(MARSDEV)/blastem

$(BLASTEM_DIR): $(BLASTEM_PKG)
	tar xf $(BLASTEM_PKG)

$(BLASTEM_PKG):
	@wget https://www.retrodev.com/blastem/nightlies/$(BLASTEM_PKG)

clean:
	rm -rf $(BLASTEM_DIR)

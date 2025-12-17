BUILDDIR ?= $(shell realpath ../../../initramfs)
DESTDIR := $(BUILDDIR)/corepack/libvos

all:
	@mkdir -p $(DESTDIR)
	gcc -c stdout.c -o $(DESTDIR)/stdout.o
	ar rcs $(DESTDIR)/libvos.a $(DESTDIR)/stdout.o
	rm -f $(DESTDIR)/stdout.o
	@echo "  -> Built $(DESTDIR)/libvos.a"

clean:
	rm -f $(DESTDIR)/*.o $(DESTDIR)/libvos.a
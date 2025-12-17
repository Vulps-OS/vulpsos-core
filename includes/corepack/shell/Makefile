# Custom Makefile for shell component
SOURCES := registry.c executor.c main.c
BUILDDIR ?= $(shell realpath ../../../initramfs)
DESTDIR := $(BUILDDIR)/corepack/shell
OBJECTS := $(addprefix $(DESTDIR)/,$(SOURCES:.c=.o))
TARGET := $(DESTDIR)/shell

.PHONY: all clean

all: $(TARGET)
	@echo "  -> Built $(TARGET)"

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) -static -o $(TARGET)
	rm -f $(OBJECTS)

$(DESTDIR)/%.o: %.c
	@mkdir -p $(DESTDIR)
	gcc -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

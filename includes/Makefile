BUILDDIR ?= $(shell realpath ../initramfs)
SOURCEDIRS := $(shell find . -mindepth 1 -type d)

.PHONY: all clean build-auto

all:
	@echo "Building all components in includes/..."
	@for dir in $(SOURCEDIRS); do \
		if [ -f "$$dir/Makefile" ]; then \
			echo "Building $$dir (custom Makefile)..."; \
			$(MAKE) -C $$dir BUILDDIR=$(BUILDDIR); \
		elif ls $$dir/*.c 1>/dev/null 2>&1; then \
			echo "Building $$dir (auto-discovery)..."; \
			$(MAKE) build-auto DIR=$$dir; \
		fi \
	done
	@echo "Build complete!"

build-auto:
	@$(eval CLEAN_DIR := $(patsubst ./%,%,$(DIR)))
	@$(eval DESTDIR := $(BUILDDIR)/$(CLEAN_DIR))
	@mkdir -p $(DESTDIR)
	@$(eval SOURCES := $(wildcard $(DIR)/*.c))
	@for src in $(SOURCES); do \
		basename=$$(basename $$src .c); \
		echo "  -> Building $$basename from $$src"; \
		gcc $$src -static -o $(DESTDIR)/$$basename; \
	done

clean:
	@echo "Cleaning build artifacts..."
	@for dir in $(SOURCEDIRS); do \
		if [ -f "$$dir/Makefile" ]; then \
			$(MAKE) -C $$dir clean; \
		fi \
	done
	@find . -name "*.o" -delete
	@echo "Clean complete!"

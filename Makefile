CFLAGS = -O3

all: purepath

purepath: purepath.c

INSTALL_FILE    = install -p -m 644
INSTALL_PROGRAM = install -p -m 755 -s

prefix_is_defined:
ifeq ($(strip $(PREFIX)),)
	$(error PREFIX is not set)
endif

install: all prefix_is_defined
	$(info Installing in $(PREFIX))
	mkdir -p $(PREFIX)/bin
	$(INSTALL_FILE) README.md $(PREFIX)
	$(INSTALL_PROGRAM) purepath $(PREFIX)/bin

clean:
	rm -f purepath

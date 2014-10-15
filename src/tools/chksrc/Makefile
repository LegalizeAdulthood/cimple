TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = chksrc
SOURCES = main.c
LIBRARIES =

include $(TOP)/mak/rules.mak

static:
	g++ -static -o chksrc main.c

install:
	cp chksrc /usr/local/bin/chksrc

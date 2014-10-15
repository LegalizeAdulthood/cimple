TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = genhnd

SOURCES = main.cpp

LIBRARIES = cimpleutil cimplegencommon cimplemof cimple

include $(TOP)/mak/rules.mak

usage:
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

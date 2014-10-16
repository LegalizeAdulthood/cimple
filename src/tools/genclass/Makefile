TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = genclass

SOURCES = main.cpp

LIBRARIES = cimpleutil cimplegencommon cimplemof cimple

include $(TOP)/mak/rules.mak

main.cpp: usage.h
usage.h: usage.txt
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

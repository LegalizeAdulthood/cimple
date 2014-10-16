TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = regview

SOURCES = main.cpp

LIBRARIES = cimpleutil cimple pegclient pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

## generate the usage.h file from the usage.txt
main.cpp: usage.h
usage.h: usage.txt
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

include ../check-pegasus.mak

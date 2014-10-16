TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = regmod

SOURCES = main.cpp

LIBRARIES = cimpleutil cimple pegclient pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

main.cpp: usage.h
usage.h: usage.txt
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

include ../check-pegasus.mak

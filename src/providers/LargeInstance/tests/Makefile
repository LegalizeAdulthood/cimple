TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = testLargeInstance

SOURCES = main.cpp

LIBRARIES = cimple pegclient pegcommon cimpleutil

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

live:
	$(TARGET) -v

manualtest:
	$(TARGET) -c 1000 -s 10000 -t 1  -v

main.cpp: usage.h
usage.h: usage.txt
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = genmod

SOURCES = main.cpp

LIBRARIES = cimplemof cimplegencommon cimpleutil cimple

INCLUDES += -I$(SRC_DIR)/mof

include $(TOP)/mak/rules.mak

main.cpp: usage.h
usage.h: usage.txt
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

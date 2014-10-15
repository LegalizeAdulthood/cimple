TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = catmod

SOURCES = main.cpp

LIBRARIES = cimpleutil cimple

INCLUDES += -I$(SRC_DIR)/mof

include $(TOP)/mak/rules.mak

usage:
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

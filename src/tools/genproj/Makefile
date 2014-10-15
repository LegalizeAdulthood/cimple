TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = genproj

SOURCES = main.cpp

LIBRARIES = cimpleutil cimple

INCLUDES += -I$(SRC_DIR)/mof -DCIMPLE_BINDIR=\"$(BINDIR_OPT)\"

include $(TOP)/mak/rules.mak

usage:
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

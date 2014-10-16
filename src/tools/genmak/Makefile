TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = genmak

SOURCES = main.cpp

LIBRARIES = cimpleutil cimple

INCLUDES += -I$(SRC_DIR)/mof -DCIMPLE_BINDIR=\"$(BINDIR_OPT)\"

DEFINES += -DCIMPLE_DATADIR=\"$(DATADIR_OPT)\"

include $(TOP)/mak/rules.mak

main.cpp: usage.h
usage.h: usage.txt
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

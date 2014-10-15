TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimplegencommon
SOURCES = gencommon.cpp
LIBRARIES = mof cimpleutil cimple
INCLUDES += -I$(SRC_DIR)/mof
DEFINES += -DGENCOMMON_INTERNAL

include $(TOP)/mak/rules.mak

tests:

usage:
	file2c usage.txt -n USAGE > usage.h

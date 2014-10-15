TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cimplegencommon
STATIC_LIBRARY = cimplegencommon_s
SOURCES = gencommon.cpp
LIBRARIES = mof cimpleutil cimple
INCLUDES += -I$(SRC_DIR)/mof
DEFINES += -DGENCOMMON_INTERNAL

include $(TOP)/mak/rules.mak

tests:

usage:
	file2c usage.txt -n USAGE > usage.h

genclass:

TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = genclass
SOURCES = main.cpp
LIBRARIES = mof cimplegencommon cimpleutil
INCLUDES += -I$(SRC_DIR)/mof

include $(TOP)/mak/rules.mak

tests:

usage:
	file2c usage.txt -n USAGE > usage.h

genclass:

TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimplegencommon
SOURCES = gencommon.cpp
LIBRARIES = -lmof -lcimpleutil -lcimple
INCLUDES += -I$(SRC)/mof

include $(TOP)/mak/rules.mak

tests:

usage:
	file2c usage.txt -n USAGE > usage.h

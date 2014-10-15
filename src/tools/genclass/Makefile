TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = genclass
SOURCES = main.cpp
LIBRARIES = -lmof -lcimplegencommon -lcimpleutil
INCLUDES += -I$(SRC)/mof

include $(TOP)/mak/rules.mak

tests:

usage:
	file2c usage.txt -n USAGE > usage.h

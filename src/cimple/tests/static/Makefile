TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_static
SOURCES = main.cpp
LIBRARIES = cimple_s
DEFINES += -DCIMPLE_CIMPLE_LINKAGE=""

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:

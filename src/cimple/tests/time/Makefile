TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_time
SOURCES = main.cpp
LIBRARIES = cimple_s
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:

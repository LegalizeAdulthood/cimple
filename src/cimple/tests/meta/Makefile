TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_meta
SOURCES = test_meta.cpp
LIBRARIES = cimple_s
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

genclass:

tests:
	@ $(BINARY_TARGET)

TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_property
SOURCES = test_property.cpp
LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

genclass:

tests:
	@ $(BINARY_TARGET)

TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_cond_queue2
SOURCES = main.cpp
LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:

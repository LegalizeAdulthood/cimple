TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_cast
SOURCES = D.cpp C.cpp B.cpp A.cpp E.cpp main.cpp
LIBRARIES = cimple_s
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:
	genclass A B C D E

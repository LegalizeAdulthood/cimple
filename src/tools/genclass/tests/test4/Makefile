TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = genclass_test4
SOURCES = Erp2.cpp main.cpp
LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	genclass -I ../mof Erp2

tests:
	@ $(BINARY_TARGET)

genclass:

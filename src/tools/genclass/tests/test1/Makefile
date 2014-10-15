TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = genclass_test1
SOURCES = Test1.cpp Test2.cpp main.cpp
LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	genclass -I ../mof Test1 Test2

tests:
	@ $(BINARY_TARGET)

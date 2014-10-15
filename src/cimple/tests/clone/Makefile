TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_clone

SOURCES = test_clone.cpp MyClass.cpp repository.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

genclass:
	genclass -r MyClass

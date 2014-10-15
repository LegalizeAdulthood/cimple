TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = genclass_test7

SOURCES = main.cpp EmbeddedClass.cpp MyClass.cpp YourClass.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:
	genclass YourClass MyClass EmbeddedClass

TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass7

SOURCES = main.cpp EmbeddedClass.cpp MyClass.cpp YourClass.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR)/genclass YourClass MyClass EmbeddedClass

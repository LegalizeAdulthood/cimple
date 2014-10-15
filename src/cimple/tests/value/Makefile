TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_value

SOURCES = main.cpp MyClass.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

run:
	$(TARGET)

VALGRIND=/opt/valgrind/bin/valgrind

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full  $(TARGET)

genclass:
	$(BINDIR)/genclass MyClass

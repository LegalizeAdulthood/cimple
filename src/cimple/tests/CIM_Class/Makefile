TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_CIM_Class

SOURCES = main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

VALGRIND=/opt/valgrind/bin/valgrind

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full  $(TARGET)


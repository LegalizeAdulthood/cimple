TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_Enc

SOURCES = main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass1

SOURCES = Test1.cpp Test2.cpp main.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -I ../mof Test1 Test2

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

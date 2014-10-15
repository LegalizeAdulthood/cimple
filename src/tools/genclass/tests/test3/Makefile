TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass3

SOURCES = Erp.cpp main.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR)/genclass -I ../mof Erp

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

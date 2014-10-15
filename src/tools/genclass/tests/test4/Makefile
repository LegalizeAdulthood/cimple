TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass4

SOURCES = Erp2.cpp main.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR)/genclass -I ../mof Erp2

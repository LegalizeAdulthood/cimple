TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = brevity_client5

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

tests:

MOF=$(CIMPLE_ROOT)/src/providers/Employee/repository.mof

gen:
	$(BINDIR)/genclass -r -M $(MOF) $(CLASSES)
	$(BINDIR)/genhnd -M $(MOF) $(CLASSES)

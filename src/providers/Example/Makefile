TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleexample

SOURCES = \
    Example.cpp \
    Example_Provider.cpp \
    House.cpp \
    module.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r Example House

genprov:
	$(BINDIR)/genprov Example

genmod:
	$(BINDIR)/genmod Example Example

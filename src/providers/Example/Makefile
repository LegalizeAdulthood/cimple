TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleexample

GENCLASS_SOURCES = \
    Example.cpp \
    House.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    Example_Provider.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Example House

genprov:
	$(BINDIR)/genprov Example

genmod:
	$(BINDIR)/genmod Example Example

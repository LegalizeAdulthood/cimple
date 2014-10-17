TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplerefarrary

GENCLASS_SOURCES = \
    RefArray.cpp \
    RefArrayParam.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    RefArray_Provider.cpp \
    module.cpp

#CIMPLE_CMPI_MODULE=1
CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r RefArray

genprov:
	$(BINDIR)/genprov RefArray

genmod:
	$(BINDIR)/genmod RefArray RefArray

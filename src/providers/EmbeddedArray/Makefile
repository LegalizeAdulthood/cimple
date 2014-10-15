TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleea

SOURCES = \
    EA_Class1.cpp \
    EA_Class2.cpp \
    EA_Class2_Provider.cpp \
    repository.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -v -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r EA_Class1 EA_Class2

genprov:
	$(BINDIR)/genprov EA_Class2

genmod:
	$(BINDIR)/genmod EA EA_Class2


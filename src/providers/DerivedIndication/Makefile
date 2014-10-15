TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplederivedindic

SOURCES = \
    CIM_Indication.cpp \
    DerivedIndication.cpp \
    DerivedIndication_Provider.cpp \
    module.cpp \
    MyIndication.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r DerivedIndication

genprov:
	$(BINDIR)/genprov DerivedIndication

genmod:
	$(BINDIR)/genmod DerivedIndication DerivedIndication

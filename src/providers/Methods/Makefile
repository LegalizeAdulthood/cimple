TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplemethods

SOURCES = \
    Arg.cpp \
    Methods.cpp \
    Methods_Provider.cpp \
    module.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r Methods

genprov:
	$(BINDIR)/genprov Methods

genmod:
	$(BINDIR)/genmod Methods Methods

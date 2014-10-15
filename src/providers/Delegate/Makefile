TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleDelegate

SOURCES = \
    Delegate.cpp \
    Delegate_Provider.cpp \
    Delegator.cpp \
    Delegator_Provider.cpp \
    repository.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r Delegate Delegator

genprov:
	$(BINDIR)/genprov Delegate
	$(BINDIR)/genprov Delegator

genmod:
	$(BINDIR)/genmod Delegate Delegate Delegator

live:
	$(CIMCLI) ei Delegate
	$(CIMCLI) ei Delegator

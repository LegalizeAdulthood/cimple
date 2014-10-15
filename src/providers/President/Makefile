TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplePresident
SOURCES = repository.cpp President.cpp module.cpp President_Provider.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak


include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r President

genprov:
	$(BINDIR)/genprov President

genmod:
	$(BINDIR)/genmod President President


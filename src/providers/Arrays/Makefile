TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplearrays

SOURCES = \
    Arrays.cpp \
    Arrays_Provider.cpp \
    module.cpp \
    repository.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/cimv2 -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r Arrays

genprov:
	$(BINDIR)/genprov Arrays

genmod:
	$(BINDIR)/genmod Arrays Arrays

live:
	$(CIMCLI) ni Arrays --sum -count 1
	$(CIMCLI) ei Arrays	--sum -count 1
manual-test:
	$(CIMCLI) ni Arrays
	$(CIMCLI) ei Arrays

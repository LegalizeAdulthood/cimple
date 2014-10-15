TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplething

SOURCES = \
    module.cpp \
    repository.cpp \
    Thing.cpp \
    ThingLink.cpp \
    ThingLink_Provider.cpp \
    Thing_Provider.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r ThingLink

genprov:
	$(BINDIR)/genprov Thing
	$(BINDIR)/genprov ThingLink

genmod:
	$(BINDIR)/genmod Thing Thing ThingLink

live:
	$(CIMCLI) ei Thing --sum -count 10
	$(CIMCLI) ni Thing --sum -count 10
	$(CIMCLI) gi Thing.key=200
	$(CIMCLI) a Thing.key=100 --sum -count 1
	$(CIMCLI) an Thing.key=100 --sum -count 1
	$(CIMCLI) r Thing.key=100 --sum -count 1
	$(CIMCLI) rn Thing.key=100 --sum -count 1

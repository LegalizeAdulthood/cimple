TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleSuper

SOURCES = \
    module.cpp repository.cpp Super.cpp Sub1.cpp Sub2.cpp Super_Provider.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r Super Sub1 Sub2

genprov:
	$(BINDIR)/genprov Super

genmod:
	$(BINDIR)/genmod Super Super

regmod:
	$(BINDIR)/regmod -s -c $(TARGET)

live:
	$(CIMCLI) ei Super
	$(CIMCLI) ni Super --sum -count 2
	$(CIMCLI) ni Sub1 --sum -count 1
	$(CIMCLI) ni Sub2 --sum -count 1

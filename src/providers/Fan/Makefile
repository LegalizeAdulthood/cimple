TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplefan

SOURCES = \
    repository.cpp \
    Fan.cpp \
    Fan_Provider.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r Fan

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genprov:
	$(BINDIR)/genprov Fan

genmod:
	$(BINDIR)/genmod Fan Fan
	
genproj:
	$(BINDIR)/genproj Fan Fan	

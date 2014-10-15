TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleea

SOURCES = \
    All_Class.cpp \
    All_Class_Provider.cpp \
    All_Part.cpp \
    module.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r All_Class

genprov:
	$(BINDIR)/genprov All_Class

genmod:
	$(BINDIR)/genmod EA All_Class

genproj:
	$(BINDIR)/genproj EA All_Class


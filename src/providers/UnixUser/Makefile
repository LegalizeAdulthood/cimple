TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleunixusrprov

GENCLASS_SOURCES = \
    UnixUser.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
    UnixUser_Provider.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r UnixUser

genprov:
	$(BINDIR)/genprov UnixUser

genmod:
	$(BINDIR)/genmod UnixUser UnixUser

regmod:
	$(BINDIR)/regmod -c $(TARGET)

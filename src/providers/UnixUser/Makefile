TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleunixusrprov

GENCLASS_SOURCES = \
    UnixUser.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
    UnixUser_Provider.cpp

CIMPLE_PEGASUS_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

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

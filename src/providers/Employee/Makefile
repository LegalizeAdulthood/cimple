TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleEmployee

GENCLASS_SOURCES = \
    Employee.cpp \
    Link.cpp \
    Manager.cpp \
    OutOfOfficeNotice.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    Employee_Provider.cpp \
    Link_Provider.cpp \
    Manager_Provider.cpp \
    OutOfOfficeNotice_Provider.cpp \
    Resource.cpp \
    module.cpp

# Allow building providers for either CMPI or Pegasus C++ provider interface
# Changing Provider interfaces requires reregistering the provider.
# Default is CMPI Provider
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_CMPI_MODULE = 1
endif

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genprov:
	$(BINDIR)/genprov Employee Manager Link OutOfOfficeNotice

genmod:
	$(BINDIR)/genmod Employee Employee Manager Link OutOfOfficeNotice

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Employee Manager Link OutOfOfficeNotice

genproj:
	$(BINDIR)/genproj Employee Employee Manager Link OutOfOfficeNotice

regmod-dump:
	$(BINDIR)/regmod -d -c $(TARGET)


## manual tests

eiemployee:
	cimcli ei employee

miemployee:
	cimcli mi employee Id=4001 Hobbies="running","sleeping","playing" \
    -pl Id,Hobbies
	cimcli gi employee Id=4001

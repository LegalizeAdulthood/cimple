TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleEmployee

SOURCES = \
    module.cpp \
    Resource.cpp \
    Employee.cpp \
    Employee_Provider.cpp \
    Link.cpp \
    Link_Provider.cpp \
    Manager.cpp \
    Manager_Provider.cpp \
    OutOfOfficeNotice.cpp \
    OutOfOfficeNotice_Provider.cpp \
    repository.cpp

####CIMPLE_CMPI_MODULE=1
####CIMPLE_PEGASUS_MODULE=1
## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider.
ifdef CIMPLE_PROVIDER_BUILD_CMPI
    CIMPLE_CMPI_MODULE=1
else
    CIMPLE_PEGASUS_MODULE=1
endif

include ../common.mak


include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genprov:
	$(BINDIR)/genprov Employee Manager Link OutOfOfficeNotice

genmod:
	$(BINDIR)/genmod Employee Employee Manager Link OutOfOfficeNotice

genclass:
	$(BINDIR)/genclass -r Employee Manager Link OutOfOfficeNotice

genproj:
	$(BINDIR)/genproj Employee Employee Manager Link OutOfOfficeNotice

regmod-dump:
	$(BINDIR)/regmod -d -c $(TARGET)

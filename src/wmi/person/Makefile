TOP=../../..

include $(TOP)/mak/config.mak

PROVIDER_MODULE = Person

Classes = Person

LIBRARY = Person

GENCLASS_SOURCES = \
    $(Classes:=.cpp) \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    Person_Provider.cpp \
    module.cpp

LIBRARIES = cimplewmiadap cimple

## Extra link flag required by wmi
EXTRA_LINK_FLAGS = /def:link.def
EXTRA_SYS_LIBS = ole32.lib oleaut32.lib

## set to use wmi adpater
DEFINES += -DCIMPLE_WMI_MODULE

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

## provider generation targets
repository.mof: wmiqualifiers.mof providerclasses.mof

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r $(Classes)

genprov:
	$(BINDIR)/genprov $(Classes)

genmod:
	$(BINDIR)/genmod $(PROVIDER_MODULE) $(Classes)

genproj:
	$(BINDIR)/genproj Person Person

## provider registration, installation and removal targets
## normally user should only need to call register
#
register:
SOURCEPATH=$(subst /,\,$(TARGET))
DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll
NAMESPACE=root\default

register: install
	mofcomp -N:$(NAMESPACE) providerclasses.mof
	mofcomp -N:$(NAMESPACE) register.mof
	regsvr32 /s $(DESTPATH)

## Removes the service registration
## Does not remove the repository or registration
## mof.
unregister:
	regsvr32 /u /s $(DESTPATH)
	del /f $(DESTPATH)

install:
	copy $(SOURCEPATH) $(DESTPATH)


restart: stop start

stop:
	net stop winmgmt

start:
	net start winmgmt

## NOTE: There is an issue with running wmic in a Makefile environment
## It does not terminate for some reason.  For the moment
## run test.bat from the command line
run:
	test.bat


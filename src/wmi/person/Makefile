TOP=../../..
include $(TOP)/mak/config.mak
PROVIDER_MODULE = Person
Classes = Person
LIBRARY = Person
SOURCES = \
    Person.cpp \
    Person_Provider.cpp \
    module.cpp \
    repository.cpp
LIBRARIES = cimplewmiadap cimple

## Extra link flag required by wmi
EXTRA_LINK_FLAGS = /def:link.def
EXTRA_SYS_LIBS = ole32.lib oleaut32.lib

## set to use wmi adpater
DEFINES += -DCIMPLE_WMI_MODULE

include $(TOP)/mak/rules.mak

## provider generation targets
genclass:
	genclass -r $(Classes)

genprov:
	genprov $(Classes)

genmod:
	genmod $(PROVIDER_MODULE) $(Classes)

genproj:
	genproj Person Person 

## provider registration, installation and removal targets
## normally user should only need to call register
# 
register:
SOURCEPATH=$(subst /,\,$(TARGET))
DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll

register: install
	mofcomp -N:root/cimv2 providerclasses.mof
	mofcomp -N:root/cimv2 register.mof
	regsvr32 /s $(DESTPATH)

## Removes the service registration
## Does not remove the repository or registration
## mof.
unregwmi:
	regsvr32 /u /s $(DESTPATH)

install:
	copy $(SOURCEPATH) c:\WINDOWS\system32\wbem


restartwmi: stop start

stop:
	net stop winmgmt

start:
	net start winmgmt

## testing
## This provider tested with wbemtest


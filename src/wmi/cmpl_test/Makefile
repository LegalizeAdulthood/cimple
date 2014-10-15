TOP=../../..
include $(TOP)/mak/config.mak
PROVIDER_MODULE = cmpl_test
Classes = cmpl_test
LIBRARY = cmpl_test
SOURCES = \
    cmpl_test.cpp \
    cmpl_test_Provider.cpp \
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
	genproj cmpl_test cmpl_test 

## provider registration, installation and removal targets
## normally user should only need to call register
# 
register:
SOURCEPATH=$(subst /,\,$(TARGET))
DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll
NAMESPACE=root\cimv2

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

## testing
## This provider tested with wbemtest


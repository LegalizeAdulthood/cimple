TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleCross

SOURCES = \
    Cross.cpp \
    Cross_Provider.cpp \
    CrossSubClass.cpp \
    CrossSubClass_Provider.cpp \
    Left.cpp \
    Left_Provider.cpp \
    Right.cpp \
    Right_Provider.cpp \
    module.cpp \
    repository.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

## Define the Namespaces to be used
NS_LEFT=root/PG_Interop
NS_RIGHT=root/cimv2

genproj:
	$(BINDIR)/genproj Cross Cross CrossSubClass Left Right

genclass:
	$(BINDIR)/genclass -r Cross

genprov:
	$(BINDIR)/genprov Cross
	$(BINDIR)/genprov CrossSubClass
	$(BINDIR)/genprov Left
	$(BINDIR)/genprov Right

genmod:
	$(BINDIR)/genmod Cross Cross CrossSubClass Left Right

regmod:
	$(BINDIR)/regmod -n $(NS_LEFT) -n $(NS_RIGHT) -c $(TARGET) Left
	$(BINDIR)/regmod -n $(NS_LEFT) -n $(NS_RIGHT) -c $(TARGET) Right
	$(BINDIR)/regmod -n $(NS_LEFT) -n $(NS_RIGHT) -c $(TARGET) Cross
	$(BINDIR)/regmod -n $(NS_LEFT) -n $(NS_RIGHT) -c $(TARGET) CrossSubClass

# unregister the providers and classes
unregister:
	$(BINDIR)/regmod -n $(NS_LEFT) -u -c $(TARGET) Left
	$(BINDIR)/regmod -n $(NS_RIGHT) -u -c $(TARGET) Right
	$(BINDIR)/regmod -n $(NS_LEFT) -n $(NS_RIGHT) -u -c $(TARGET) Cross
	$(BINDIR)/regmod -n $(NS_LEFT) -n $(NS_RIGHT) -u -c $(TARGET) CrossSubClass

## The following is a purely Pegasus capability and requires running server
## Useful for complete cleanup if model has changed for this provider
reregister:
	cimprovider -d -m Cross_Module
	$(MAKE) unregister
	$(MAKE) insmod
	$(MAKE) regmod

##============================================================================
##
## Live manual tests using Pegasus cimcli
## These tests are a demonstration that the provider works.  They
## do not test the results today, simply assure that there is no exception
## on response
##
##===========================================================================	
manual-test:
	cimcli ei Cross
	cimcli ei Left
	cimcli ei Right
	cimcli  an Left.key=1 -n $(NS_LEFT)
	cimcli  an Right.key=1 -n $(NS_RIGHT)
	cimcli  a Left.key=1 -n $(NS_LEFT)
	cimcli  a Right.key=1 -n $(NS_RIGHT)





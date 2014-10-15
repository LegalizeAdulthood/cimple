TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

## Define Provider, Class names and test namespace
TEST_CLASS = CMPL_LargeInstance
SHARED_LIBRARY = cimpleLargeInstances
TEST_NAMESPACE=root/cimv2


SOURCES = \
    CMPL_LargeInstance.cpp \
    CMPL_LargeInstance_Provider.cpp \
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

## Generate the class. First step in writing the provider once mof exists in repository.mof
genclass:
	$(BINDIR)/genclass -r $(TEST_CLASS)

## Generate the Provider.  Run this after genclass target
genprov:
	$(BINDIR)/genprov $(TEST_CLASS)

## Generate the Module.  Run this after genprov target
genmod:
	$(BINDIR)/genmod CMPL_LargeInstance $(TEST_CLASS)

## Alternative to genclass, genprov, genmod in a single step.
genproj:
	$(BINDIR)/genproj CMPL_LargeInstance $(TEST_CLASS)

## Provider registration and installation
##
## Register the provider. Note that this does not actually install the
## provider. This target may be used manually and is used by the
## cimple test environment
regmod:
	$(BINDIR)/regmod  -c $(TARGET)
	
unregister:
	$(BINDIR)/regmod -u -c $(Target) $(TEST_CLASS)

remove:
	$(BINDIR)/regmod  -u -c $(Target) $(TEST_CLASS)
	
##============================================================================
##
## The following rule registers this provider with the SFCB.
##
##============================================================================

## This may change per users needs
SFCB_MOFSDIR=/usr/local/var/lib/sfcb/stage/mofs/root/cimv2
SFCB_REGSDIR=/usr/local/var/lib/sfcb/stage/regs

register-sfcb:
	cp $(TARGET) /usr/lib64/
	cp All_Class.mof $(SFCB_MOFSDIR)/All_Class.mof
	cp All_Part.mof $(SFCB_MOFSDIR)/All_Part.mof 
	cp All_Class.reg $(SFCB_REGSDIR)/All_Class.reg
	sfcbrepos

##============================================================================
##
## Live manual tests using Pegasus cimcli
## These tests are a demonstration that the provider works.  They
## do not test the results today, simply assure that there is no exception
## on response
##
##===========================================================================	
manual-test:
	cimcli ns -l localhost
	cimcli gc $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)
	cimcli ni $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)
	cimcli ei $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)

ei:
	cimcli ei $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)

gc:
	cimcli gc $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)

gi:
	cimcli gi $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)
		
pl1:
	cimcli ei $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE) -niq \
       -pl Key,sizeOfInstance,largeProperty

pl2:
	cimcli ei $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE) -niq \
       -pl Key,sizeOfInstance,largeArrayProperty

setconfig:
	cimcli im $(TEST_CLASS) Key=1 -l localhost -n $(TEST_NAMESPACE) \
    setconfig

getconfig:
	cimcli im $(TEST_CLASS).Key=1 getconfig -l localhost -n $(TEST_NAMESPACE) 

testmethod:
	cimcli im $(TEST_CLASS) test -l localhost -n $(TEST_NAMESPACE)
   

##===========================================================================
## Manual commands to make this CMPI provider
##===========================================================================
cmpi:
	$(MAKE) clean
	-cimserver -s
	export CIMPLE_PROVIDER_TYPE=CMPI 
	$(MAKE)
	$(MAKE) insmod
	cimserver
	$(MAKE) register
    
    
	


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

TEST_NAMESPACE=root/cimv2

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider.
ifdef CIMPLE_PROVIDER_BUILD_CMPI
    CIMPLE_CMPI_MODULE=1
else
    CIMPLE_PEGASUS_MODULE=1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

register:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r All_Class

genprov:
	$(BINDIR)/genprov All_Class

genmod:
	$(BINDIR)/genmod EA All_Class

genproj:
	$(BINDIR)/genproj EA All_Class
	
unregister:
	$(BINDIR)/regmod -v -u -c $(TARGET)

	
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
##===========================================================================	
manual-test:
	cimcli ns -l localhost
	cimcli gc All_Class -l localhost -n $(TEST_NAMESPACE)
	cimcli ni All_Class -l localhost -n $(TEST_NAMESPACE)
	cimcli ei All_Class -l localhost -n $(TEST_NAMESPACE)

ei:
	cimcli ei All_Class -l localhost -n $(TEST_NAMESPACE)
		
pl1:
	cimcli ei All_Class -l localhost -n $(TEST_NAMESPACE) -niq -pl Key,uint8Scalar,booleanScalar

pl2:
	cimcli ei All_Class -l localhost -n $(TEST_NAMESPACE) -niq -pl uint8Scalar,booleanScalar

pl3:
	cimcli ei All_Class -l localhost -n $(TEST_NAMESPACE) -pl uint8Scalar

gi:
	cimcli gi All_Class -l localhost -n $(TEST_NAMESPACE) -pl Key,uint8Scalar

##===========================================================================
## Manual commands to make this CMPI provider
##===========================================================================
cmpi:
	$(MAKE) clean
	-cimserver -s
	export CIMPLE_PROVIDER_BUILD_CMPI=1 
	$(MAKE)
	$(MAKE) insmod
	cimserver
	$(MAKE) register
    
    
	


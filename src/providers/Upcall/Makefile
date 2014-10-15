TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleupcall

SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    module.cpp \
    repository.cpp \
    Upcall.cpp \
    Upcall_Provider.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r Upcall CIM_ComputerSystem

genprov:
	$(BINDIR)/genprov Upcall

genmod:
	$(BINDIR)/genmod Upcall Upcall

genproj:
	$(BINDIR)/genproj Upcall Upcall CIM_ComputerSystem

regmod:
	$(BINDIR)/regmod -c $(TARGET)

##============================================================================
##
## Live manual tests using Pegasus cimcli
## These tests are a demonstration that the provider works.  They
## do not test the results today, simply assure that there is no exception
## on response
##===========================================================================	
manual-test:
	cimcli gc Upcall
	cimcli ni Upcall
	cimcli ei Upcall

## Start the execution of the repetitive test of an upcall
## There are two parameters on the call count and delay
## each is a Uint32. Count if nonzero defines the number
## of repetitions.  Delay if nonzero defines the delay in
## milliseconds between each repetition of the upcall
starttest:
	cimcli im Upcall StartTest count=100

## stop a test that is being executed.
stoptest:
	cimcli im Upcall StopTest

##============================================================================
##
## Live tests that are executed as part of the CIMPLE regression tests
##             These tests use Pegasus cimcli
## 
##===========================================================================	
live:
	cimcli ni Upcall
	cimcli ei Upcall
	cimcli im Upcall StartTest count=1000
	$(SLEEP) 3
	cimcli im Upcall StopTest

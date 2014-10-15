TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = StringArrayProvider
TEST_CLASS = StringArrayClass

SOURCES = \
    module.cpp \
    repository.cpp \
    StringArrayClass.cpp \
    StringArrayClass_Provider.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_CMPI_MODULE = 1
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
	$(BINDIR)/genmod  StringArray $(TEST_CLASS)

## Alternative to genclass, genprov, genmod in a single step.
genproj:
	$(BINDIR)/genproj StringArray $(TEST_CLASS)

regmod:
	$(BINDIR)/regmod -c $(TARGET)

live:
	cimcli ei $(TEST_CLASS) -n root/cimv2
	cimcli gi $(TEST_CLASS) Key=1
	cimcli ci $(TEST_CLASS) Key=3 Colors=white,green
	cimcli gi $(TEST_CLASS) Key=3

test1:
	cimcli ci $(TEST_CLASS) Key=2 sizes=1,2

test2:
	cimcli gi $(TEST_CLASS) Key=2

test3:
	cimcli gi $(TEST_CLASS) Key=1

gc:
	cimcli gc $(TEST_CLASS)

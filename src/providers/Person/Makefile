TOP = ../../..
include $(TOP)/mak/config.mak

## Defines this as a provider module to the CIMPLE make environment
## The target insmod can be used to install the provider shared library
MODULE=1

SHARED_LIBRARY = cimplePerson

## List of classes for this provider is in a file classlist in the provider
## directory

SOURCES = \
    repository.cpp \
    Person.cpp \
    Salesman.cpp \
    PersonLink.cpp \
    SalesmanLink.cpp \
    Person_Provider.cpp \
    PersonLink_Provider.cpp \
    Salesman_Provider.cpp \
    SalesmanLink_Provider.cpp \
    module.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

###############################################################################
##
## CIMPLE tool targets to build the classes, providers, and module
##
###############################################################################

genclass:
	$(BINDIR)/genclass -r -F classlist

genprov:
	$(BINDIR)/genprov -F classlist	

genmod:
	$(BINDIR)/genmod Person -F classlist

## As an alternate to getclass, genprov, and genproj you can use the
## following which does all three commands.
genproj:
	$(BINDIR)/genproj Person -F classlist

regmod:
	$(BINDIR)/regmod -c $(TARGET)

unregister:
	$(BINDIR)/regmod -u -c $(TARGET)

###############################################################################
##
## Manual demonstration tests using cimcli. NOTE: Requires 2.10 cimcli
##        for some of the tests (ex. ci)
##
###############################################################################
eiperson:
	$(CIMCLI) ei Person

ni:
	$(CIMCLI) ni Person
	$(CIMCLI) ni PersonLink

giperson:
	$(CIMCLI) gi Person

di:
	$(CIMCLI) di Person ssn=20

ci:
	$(CIMCLI) ci Person ssn=20 first=new last=Person

mi:
	$(CIMCLI) mi Person ssn=20 first=fred last=futz -pl last

a:
	$(CIMCLI) a Person.ssn=1

r:
	$(CIMCLI) r Person.ssn=1

hello:
	ciminvoke Person.ssn=1 hello message="hi there"

hello2:
	cimcli im Person.ssn=2 hello message="hi again"

## The following target tests the modifyInstance function with 
## propertylist.  However, since Pegasus only added some of the
## functionality used in this test as part of Pegasus 2.10 it is set
## as a completely separate test. Specifically the ci and mi were incomplete
## in earlier versions of cimcli. This test will fail if run against
## earlier versions of cimcli.
live_testmi:
	$(CIMCLI) ci Person ssn=21 first=create last=instance
	$(CIMCLI) ti Person ssn=21 first=create last=instance
##  modify both properties
	$(CIMCLI) mi Person ssn=21 first=modify1 last=sameinstance
	$(CIMCLI) ti Person ssn=21 first=modify1 last=sameinstance
##  modify both properties in instance but server modifies only first
	$(CIMCLI) mi Person ssn=21 first=modify2 last=sameinstanceagain -pl first
	$(CIMCLI) ti Person ssn=21 first=modify2 last=sameinstance
##  modify both properties in instance bur server modifies only last
	$(CIMCLI) mi Person ssn=21 first=modify3 last=blah -pl last
	$(CIMCLI) ti Person ssn=21 first=modify2 last=blah
	$(CIMCLI) di Person ssn=21          

## cimcli based test of the provider.  Tests for existence and quantities
## on a number of operations
live:
	$(CIMCLI) gi Person.ssn=1
	$(CIMCLI) ni Person  --sum -count 7
	$(CIMCLI) ni PersonLink
	$(CIMCLI) ni PersonLink --sum -count 7 
	$(CIMCLI) ni Salesman --sum -count 2
	$(CIMCLI) ni SalesmanLink --sum -count 1
	
	$(CIMCLI) ei Person
	$(CIMCLI) ei Person --sum -count 7
	$(CIMCLI) ei PersonLink
	$(CIMCLI) ei PersonLink --sum -count 7
	$(CIMCLI) ei Salesman --sum -count 2
	$(CIMCLI) ei SalesmanLink --sum -count 1

	$(CIMCLI) an Person --sum -count 1
	$(CIMCLI) an Person.ssn=1 --sum -count 3
	$(CIMCLI) an Person.ssn=2 --sum -count 3
	$(CIMCLI) an Person.ssn=3 --sum -count 2
	$(CIMCLI) an Person.ssn=4 --sum -count 2
	$(CIMCLI) an Person.ssn=5 --sum -count 2

## duplicate requests to test reported issue concerning
## differences in response in subsequent requests.
	$(CIMCLI) a Person.ssn=1 --sum -count 3
	$(CIMCLI) a Person.ssn=1 --sum -count 3
	$(CIMCLI) a Person.ssn=2 --sum -count 3
	$(CIMCLI) a Person.ssn=2 --sum -count 3
	$(CIMCLI) a Person.ssn=3 --sum -count 2
	$(CIMCLI) a Person.ssn=3 --sum -count 2
	$(CIMCLI) a Person.ssn=4 --sum -count 2
	$(CIMCLI) a Person.ssn=4 --sum -count 2
	$(CIMCLI) a Person.ssn=5 --sum -count 2
	$(CIMCLI) a Person.ssn=5 --sum -count 2
	$(CIMCLI) a Person.ssn=4 --sum -count 2

	$(CIMCLI) rn Person.ssn=1 --sum -count 3
	$(CIMCLI) rn Person.ssn=2 --sum -count 3
	$(CIMCLI) rn Person.ssn=3 --sum -count 2
	$(CIMCLI) rn Person.ssn=4 --sum -count 2
	$(CIMCLI) rn Person.ssn=5 --sum -count 2

	$(CIMCLI) r Person.ssn=1 --sum -count 3
	$(CIMCLI) r Person.ssn=2 --sum -count 3
	$(CIMCLI) r Person.ssn=3 --sum -count 2
	$(CIMCLI) r Person.ssn=4 --sum -count 2
	$(CIMCLI) r Person.ssn=5 --sum -count 2
	@echo +++++++++ Passed Person Provider live test


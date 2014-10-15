TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplePerson

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

## Allow building providers for eithe CMPI or Pegasus C++
ifdef CIMPLE_PROVIDER_BUILD_CMPI
   CIMPLE_CMPI_MODULE=1
else
   CIMPLE_PEGASUS_MODULE=1
endif

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r Person PersonLink Salesman SalesmanLink

genprov:
	$(BINDIR)/genprov Person
	$(BINDIR)/genprov PersonLink
	$(BINDIR)/genprov Salesman
	$(BINDIR)/genprov SalesmanLink

genmod:
	$(BINDIR)/genmod Person Person PersonLink Salesman SalesmanLink

live:
	$(CIMCLI) gi Person.ssn=1
	$(CIMCLI) ni Person  --sum -count 6
	$(CIMCLI) ni PersonLink
	$(CIMCLI) ni PersonLink --sum -count 5 
	$(CIMCLI) ni Fan --sum -count 3
	
	$(CIMCLI) ei Person
	$(CIMCLI) ei Person --sum -count 6
	$(CIMCLI) ei PersonLink
	$(CIMCLI) ei PersonLink --sum -count 5
	$(CIMCLI) ei Fan --sum -count 3
	
	$(CIMCLI) an Person 
	$(CIMCLI) an Person.ssn=1 --sum -count 2
	$(CIMCLI) an Person.ssn=2 --sum -count 2
	$(CIMCLI) an Person.ssn=3 --sum -count 2
	$(CIMCLI) an Person.ssn=4 --sum -count 2
	$(CIMCLI) an Person.ssn=5 --sum -count 0
	
	$(CIMCLI) a Person.ssn=1 --sum -count 2
	$(CIMCLI) a Person.ssn=2 --sum -count 2
	$(CIMCLI) a Person.ssn=3 --sum -count 2
	$(CIMCLI) a Person.ssn=4 --sum -count 2
	$(CIMCLI) a Person.ssn=5 --sum -count 0
	
	$(CIMCLI) r Person.ssn=1
	$(CIMCLI) r Person.ssn=2
	$(CIMCLI) r Person.ssn=3
	$(CIMCLI) r Person.ssn=4
	$(CIMCLI) r Person.ssn=5
	
	$(CIMCLI) rn Person.ssn=1 --sum -count 2
	$(CIMCLI) rn Person.ssn=2 --sum -count 2
	$(CIMCLI) rn Person.ssn=3 --sum -count 2
	$(CIMCLI) rn Person.ssn=4 --sum -count 2
	$(CIMCLI) rn Person.ssn=5 --sum -count 0


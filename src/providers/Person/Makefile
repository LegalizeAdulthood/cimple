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

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -v -c $(TARGET)

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
	$(CIMCLI) ni Person
	$(CIMCLI) ni PersonLink
	$(CIMCLI) ni PersonLink
	$(CIMCLI) ni Fan
	$(CIMCLI) ei Person
	$(CIMCLI) ei PersonLink
	$(CIMCLI) ei PersonLink
	$(CIMCLI) ei Fan
	$(CIMCLI) an Person
	$(CIMCLI) an Person.ssn=1
	$(CIMCLI) an Person.ssn=2
	$(CIMCLI) an Person.ssn=3
	$(CIMCLI) an Person.ssn=4
	$(CIMCLI) an Person.ssn=5
	$(CIMCLI) a Person.ssn=1
	$(CIMCLI) a Person.ssn=2
	$(CIMCLI) a Person.ssn=3
	$(CIMCLI) a Person.ssn=4
	$(CIMCLI) a Person.ssn=5
	$(CIMCLI) r Person.ssn=1
	$(CIMCLI) r Person.ssn=2
	$(CIMCLI) r Person.ssn=3
	$(CIMCLI) r Person.ssn=4
	$(CIMCLI) r Person.ssn=5
	$(CIMCLI) rn Person.ssn=1
	$(CIMCLI) rn Person.ssn=2
	$(CIMCLI) rn Person.ssn=3
	$(CIMCLI) rn Person.ssn=4
	$(CIMCLI) rn Person.ssn=5

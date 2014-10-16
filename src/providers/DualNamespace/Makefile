TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleDualNamespace

GENCLASS_SOURCES = \
    DualNamespace1.cpp \
    DualNamespace2.cpp \
    repository.cpp

GENCLASS_HEADERS = \
    DualNamespace1.h \
    DualNamespace2.h

SOURCES = \
    $(GENCLASS_SOURCES) \
    DualNamespace1_Provider.cpp \
    DualNamespace2_Provider.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES) $(GENCLASS_HEADERS): repository.mof
	$(BINDIR)/genclass -r DualNamespace1 DualNamespace2

genprov:
	$(BINDIR)/genprov DualNamespace1 DualNamespace2

genmod:
	$(BINDIR)/genmod DualNamespace DualNamespace1 DualNamespace2

regmod1:
	$(BINDIR)/regmod -n ns1 -v -c $(TARGET) DualNamespace1

regmod2:
	$(BINDIR)/regmod -d -n ns2 -v -c $(TARGET) DualNamespace2

DualNamespace1_Provider.cpp: DualNamespace1_Provider.h
DualNamespace2_Provider.cpp: DualNamespace2_Provider.h
DualNamespace1_Provider.h: DualNamespace1.h
DualNamespace2_Provider.h: DualNamespace2.h

TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleDualNamespace

SOURCES = \
    DualNamespace1.cpp \
    DualNamespace1_Provider.cpp \
    DualNamespace2.cpp \
    DualNamespace2_Provider.cpp \
    module.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r DualNamespace1 DualNamespace2

genprov:
	$(BINDIR)/genprov DualNamespace1 DualNamespace2

genmod:
	$(BINDIR)/genmod DualNamespace DualNamespace1 DualNamespace2

regmod1:
	$(BINDIR)/regmod -n ns1 -v -c $(TARGET) DualNamespace1

regmod2:
	$(BINDIR)/regmod -d -n ns2 -v -c $(TARGET) DualNamespace2


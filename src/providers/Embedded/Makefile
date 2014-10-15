TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleemb

SOURCES = \
    CMPL_Embedded1.cpp \
    CMPL_Embedded2.cpp \
    CMPL_Embedded3.cpp \
    CMPL_Embedded.cpp \
    CMPL_Embedded_Provider.cpp \
    module.cpp \
    repository.cpp

#CIMPLE_CMPI_MODULE=1
CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r CMPL_Embedded

genprov:
	$(BINDIR)/genprov CMPL_Embedded

genmod:
	$(BINDIR)/genmod CMPL_Embedded CMPL_Embedded

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genproj:
	$(BINDIR)/genproj CMPL_Embedded CMPL_Embedded

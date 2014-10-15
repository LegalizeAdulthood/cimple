TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpletime

SOURCES = \
    CMPL_Time.cpp \
    CMPL_Time_Provider.cpp \
    module.cpp \
    repository.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r CMPL_Time

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genprov:
	$(BINDIR)/genprov CMPL_Time

genmod:
	$(BINDIR)/genmod CMPL_Time CMPL_Time

genproj:
	$(BINDIR)/genproj CMPL_Time CMPL_Time

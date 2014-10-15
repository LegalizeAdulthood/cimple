TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpletime

SOURCES = \
    CMPL_Time.cpp \
    CMPL_Time_Provider.cpp \
    module.cpp \
    repository.cpp

## Allow building providers for either CMPI or Pegasus C++
ifdef CIMPLE_PROVIDER_BUILD_CMPI
   CIMPLE_CMPI_MODULE=1
else
   CIMPLE_PEGASUS_MODULE=1
endif

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
	
manual-test:
	ciminvoke CMPL_Time SetTime Time=20070101120000.123456-360
	ciminvoke CMPL_Time GetTime
    

TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplePresident

GENCLASS_SOURCES = repository.cpp President.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) \
    module.cpp President_Provider.cpp

CIMPLE_CMPI_MODULE=1
#CIMPLE_PEGASUS_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r President

genprov:
	$(BINDIR)/genprov President

genmod:
	$(BINDIR)/genmod President President
	
genproj:
	$(BINDIR)/genproj President President	


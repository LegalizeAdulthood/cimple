TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov1

CLASSES = Test1

GENCLASS_SOURCES = $(CLASSES:=.cpp)

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp Test1_Provider.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	@ $(BINDIR)/test_genprov1

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass $(CLASSES)

genprov:
	$(BINDIR)/genprov Test1

genmod:
	$(BINDIR)/genmod Test1 Test1

Test1_Provider.h: Test1.h

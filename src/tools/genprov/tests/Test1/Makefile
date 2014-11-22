TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov1

CLASSES = Test1

GENCLASS_HEADERS = $(CLASSES:=.h)

GENCLASS_SOURCES = $(CLASSES:=.cpp)

SOURCES = $(GENCLASS_SOURCES) main.cpp Test1_Provider.cpp

LIBRARIES = cimple

CLEAN += $(GENCLASS_HEADERS) $(GENCLASS_SOURCES)

include $(TOP)/mak/rules.mak

tests:
	@ $(BINDIR)/test_genprov1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass $(CLASSES)

genprov:
	$(BINDIR)/genprov Test1

genmod:
	$(BINDIR)/genmod Test1 Test1

TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov2

CLASSES = Test2 Test2Link

GENCLASS_HEADERS = $(CLASSES:=.h)
GENCLASS_SOURCES = $(CLASSES:=.cpp)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp \
    Test2_Provider.cpp \
    Test2Link_Provider.cpp

LIBRARIES = cimple

CLEAN += $(GENCLASS_HEADERS) $(GENCLASS_SOURCES)

include $(TOP)/mak/rules.mak

tests:
	@ $(BINDIR)/test_genprov2

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass $(CLASSES)

genprov:
	$(BINDIR)/genprov  -f Test2
	$(BINDIR)/genprov  -f Test2Link

genmod:
	$(BINDIR)/genmod Test2 Test2 Test2Link

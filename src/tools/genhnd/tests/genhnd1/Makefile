TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genhnd1

CLASSES = \
    Assoc1 \
    Assoc2 \
    Class1 \
    Class2 \
    Class3 \
    Part \
    President \
    SubClass \
    Successor \
    SuperClass \
    Whole

GENCLASS_SOURCES = \
    $(CLASSES:=.cpp) \
    repository.cpp \

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

CLEAN += $(GENCLASS_HEADERS) $(GENCLASS_SOURCES)

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r $(CLASSES)

genhnd:
	$(BINDIR)/genhnd $(CLASSES)

gen: genclass genhnd

vg:
	$(VALGRIND) $(TARGET)


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

GENHND_HEADERS = \
    Class1_Hnd.h \
    Created Assoc1_Hnd.h \
    Class2_Hnd.h \
    Assoc2_Hnd.h \
    Class3_Hnd.h \
    Part_Hnd.h \
    President_Hnd.h \
    SuperClass_Hnd.h \
    SubClass_Hnd.h \
    Successor_Hnd.h \
    Whole_Hnd.h

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS) $(GENHND_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r $(CLASSES)

main.cpp: $(GENHND_HEADERS)
genhnd $(GENHND_HEADERS):
	$(BINDIR)/genhnd $(CLASSES)

gen: genclass genhnd

vg:
	$(VALGRIND) $(TARGET)


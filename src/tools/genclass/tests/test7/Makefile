TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass7

CLASSES = YourClass MyClass EmbeddedClass

GENCLASS_SOURCES = $(CLASSES:=.cpp)

GENCLASS_HEADERS = $(CLASSES:=.h)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

$(GENCLASS_SOURCES) $(GENCLASS_HEADERS): genclass

genclass: repository.mof
	$(BINDIR)/genclass $(CLASSES)

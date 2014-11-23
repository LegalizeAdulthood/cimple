TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_ref

GENCLASS_SOURCES = \
    X.cpp \
    Y.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r X Y

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

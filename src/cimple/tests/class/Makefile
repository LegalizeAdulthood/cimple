TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_class

GENCLASS_SOURCES = X.cpp Y.cpp Z.cpp AX.cpp AY.cpp AZ.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass X Y Z AX AY AZ

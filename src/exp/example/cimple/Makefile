TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = cimple_example

GENCLASS_SOURCES = \
    TheClass.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
	main.cpp \
	example.cpp \
	TheClass_Provider.cpp \
	module.cpp

LIBRARIES = cimple

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass TheClass

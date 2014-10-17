TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = cimple_example
GENCLASS_SOURCES = \
    TheClass.cpp
SOURCES = \
    $(GENCLASS_SOURCES) \
	main.cpp \
	example.cpp \
	TheClass_Provider.cpp \
	module.cpp
LIBRARIES = cimple
FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass TheClass

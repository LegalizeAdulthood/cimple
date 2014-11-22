TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplemyindic

GENCLASS_SOURCES = \
    CIM_Indication.cpp \
    MyEmbeddedClass.cpp \
    MyIndication.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
    MyIndication_Provider.cpp

CIMPLE_PEGASUS_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

ifdef CIMPLE_WINDOWS_MSVC
    DEV_NULL=.dev.null
else
    DEV_NULL=/dev/null
endif

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r MyIndication MyEmbeddedClass

genprov:
	$(BINDIR)/genprov MyIndication

genmod:
	$(BINDIR)/genmod MyIndication MyIndication

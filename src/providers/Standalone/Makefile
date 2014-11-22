TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Standalone

GENCLASS_SOURCES = \
    Standalone.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
    Standalone_Provider.cpp

LIBRARIES = cimple cimplecmpiadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

##==============================================================================
##
## Rule to register the provider with Pegasus.
##
##==============================================================================

reg:
	regmod -n root/cimv2 -c $(SHARED_LIBRARY_TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Standalone

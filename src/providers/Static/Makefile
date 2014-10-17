TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Static

DEFINES += -DCIMPLE_CIMPLE_LINKAGE=""

GENCLASS_SOURCES = \
    Static.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
    Static_Provider.cpp

LIBRARIES = cimplecmpiadap_s cimple_s

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## Rule to register the provider with Pegasus.
##
##==============================================================================

reg:
	regmod -n root/cimv2 -c $(SHARED_LIBRARY_TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Static

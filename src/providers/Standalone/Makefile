TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Standalone

SOURCES = module.cpp repository.cpp Standalone.cpp Standalone_Provider.cpp

LIBRARIES = cimple cimplecmpiadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## Rule to register the provider with Pegasus.
##
##==============================================================================

reg:
	regmod -n root/cimv2 -c $(SHARED_LIBRARY_TARGET)

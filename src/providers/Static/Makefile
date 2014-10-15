TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Static

DEFINES += -DCIMPLE_CIMPLE_LINKAGE=""

SOURCES = module.cpp repository.cpp Static.cpp Static_Provider.cpp

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

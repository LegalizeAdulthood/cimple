TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Super

SOURCES = \
    module.cpp repository.cpp Super.cpp Sub1.cpp Sub2.cpp Super_Provider.cpp

ifdef USE_CMPI
    LIBRARIES += cimplecmpiadap
    DEFINES += -DUSE_CMPI
else
    LIBRARIES += cimplepegadap
endif

LIBRARIES += cimple 

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## Rule to generate the classes
##
##==============================================================================

genclass:
	genclass -r Super Sub1 Sub2

##==============================================================================
##
## Rule to register the provider with Pegasus.
##
##==============================================================================

reg:
	regmod -d -s -c $(SHARED_LIBRARY_TARGET)

tests:

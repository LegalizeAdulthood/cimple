TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplthing

INCLUDES += -I$(TOP)/src/providers/repository 
INCLUDES += -I$(TOP)/src/CMPI/cmpi
INCLUDES += $(CMPI_INCLUDES)
INCLUDES += -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

SOURCES = Thing_Provider.cpp ThingLink_Provider.cpp module.cpp

LIBRARIES = cmplrep cimple

LIBRARIES += cimplecmpiadap

include $(TOP)/mak/rules.mak

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:

genclass:

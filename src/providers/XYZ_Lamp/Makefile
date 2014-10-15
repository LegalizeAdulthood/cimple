TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = XYZ_Lamp

INCLUDES += -I../repository -I$(TOP)/src/CMPI/cmpi \
    -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

SOURCES = XYZ_Lamp_Provider.cpp XYZ_LampLink_Provider.cpp XYZ_LampIndic_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplecmpiadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

genclass:

tests:

TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = Lamp

INCLUDES += -I../repository -I$(TOP)/src/CMPI/cmpi \
    -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

SOURCES = Lamp_Provider.cpp LampLink_Provider.cpp LampIndic_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplecmpiadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -c $(TARGET)

genclass:

tests:

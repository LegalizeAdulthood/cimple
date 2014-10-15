TOP = ../../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = ModelProvider

SOURCES = Model.cpp Part.cpp Model_Provider.cpp module.cpp

LIBRARIES = -lcimplecmpi -lcmplrep -lcimple

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

INCLUDES += $(CMPI_INCLUDES) -I$(TOP)/src/CMPI/cmpi

FLAGS += -fno-rtti -fno-exceptions

include $(TOP)/mak/rules.mak

reg:
	regmod -c -m $(TARGET)

genclass:
	$(BIN)/genclass Model Part

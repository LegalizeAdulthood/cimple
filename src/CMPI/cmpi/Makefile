TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimplecmpi

SOURCES = CMPI.cpp Converter.cpp Converter_IO.cpp Adapter.cpp

LIBRARIES = -lcimple

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

DEFINES += -DCIMPLE_NEED_CMPI_IO

INCLUDES += $(CMPI_INCLUDES)

FLAGS += -fno-rtti -fno-exceptions

include $(TOP)/mak/rules.mak

tests:

genclass:

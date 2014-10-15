TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimplecmpi

SOURCES = CMPI.cpp Converter.cpp Converter_IO.cpp Adapter.cpp version.cpp

LIBRARIES = cimple

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

DEFINES += -DCIMPLE_NEED_CMPI_IO -DCIMPLECMPL_INTERNAL

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

genclass:

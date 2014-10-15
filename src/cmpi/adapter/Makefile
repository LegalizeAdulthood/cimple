TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimplecmpiadap

SOURCES = \
    CMPI_Thread_Context.cpp \
    Converter.cpp \
    Converter_IO.cpp \
    CMPI_Adapter.cpp \

LIBRARIES = cimple

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

DEFINES += -DCIMPLE_NEED_CMPI_IO
DEFINES += -DCIMPLECMPL_INTERNAL

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

genclass:

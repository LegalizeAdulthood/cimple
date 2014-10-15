TOP = ../../..
include $(TOP)/mak/config.mak

STATIC_LIBRARY = cimplecmpiadap_s
DEFINES += -DCIMPLE_CIMPLE_LINKAGE=""
LIBRARIES = cimple_s

SOURCES = \
    CMPI_Thread_Context.cpp \
    Converter.cpp \
    CMPI_Adapter.cpp \

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI
DEFINES += -DCIMPLE_NEED_CMPI_IO
DEFINES += -DCIMPLECMPL_INTERNAL

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

genclass:

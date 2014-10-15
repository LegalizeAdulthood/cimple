TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

## Define the following variable to include extra debugging tools into
## the CMPI adapter. This is experimental and purely a debug tool
## It provides display, etc. utiliites for cmpi entities. To enable this
## uncomment the following variable.
//CMPI_ADAPTER_DEBUG = 1

LIBRARY = cimplecmpiadap

LIBRARIES = cimple

SOURCES = \
    CMPI_Containers.cpp \
    CMPI_Thread_Context.cpp \
    Converter.cpp \
    CMPI_Adapter.cpp

ifdef CMPI_ADAPTER_DEBUG
    SOURCES += CMPIUtils.cpp
    DEFINES += -DCMPI_ADAPTER_DEBUG
endif

ifeq ($(CMPI_VOID_RETURN_BUG_OPT),1)
  DEFINES += -DCIMPLE_HAVE_CMPI_VOID_RETURN_BUG
endif

INCLUDES += -I$(WITH_CMPI_OPT)

include $(TOP)/mak/rules.mak
include ../check-cmpi.mak

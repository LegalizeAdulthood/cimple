TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimplecmpiadap

LIBRARIES = cimple

SOURCES = \
    CMPI_Containers.cpp \
    CMPI_Thread_Context.cpp \
    Converter.cpp \
    CMPI_Adapter.cpp

ifeq ($(CMPI_VOID_RETURN_BUG_OPT),1)
  DEFINES += -DCIMPLE_HAVE_CMPI_VOID_RETURN_BUG
endif

ifeq ($(CMPI_ENUM_INSTANCES_BUG_OPT),1)
  DEFINES += -DCIMPLE_HAVE_CMPI_ENUM_INSTANCES_BUG
endif

ifeq ($(CMPI_MODIFY_INSTANCE_BUG_OPT),1)
  DEFINES += -DCIMPLE_HAVE_CMPI_MODIFY_INSTANCE_BUG
endif

INCLUDES += -I$(WITH_CMPI_OPT)

include $(TOP)/mak/rules.mak
include ../check-cmpi.mak

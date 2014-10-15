TOP = ../../..
include $(TOP)/mak/config.mak

ifeq ($(PLATFORM),VXWORKS_XSCALE_GNU)
  INSTALL=1
endif

STATIC_LIBRARY = cimplepegutils

SOURCES = \
    print.cpp \
    Containers.cpp \
    Converter.cpp

LIBRARIES = \
    pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak
include ../check-pegasus.mak

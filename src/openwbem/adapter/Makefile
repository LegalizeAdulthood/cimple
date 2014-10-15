TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimpleowadap

SOURCES = \
    OpenWBEM_Adapter.cpp \
    Converter.cpp  

LIBRARIES = \
    owprovider \
    owcppprovifc \
    openwbem \
    cimple

INCLUDES += -I$(WITH_OPENWBEM_OPT)/include

LINK_FLAGS += -L$(WITH_OPENWBEM_OPT)/lib

include $(TOP)/mak/rules.mak

INSTALL_HEADERS_DIR = cimple

INSTALL_HEADERS = \
    OpenWBEM_Adapter.h

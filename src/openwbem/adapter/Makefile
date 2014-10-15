TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cimpleowadap
STATIC_LIBRARY = cimpleowadap_s

SOURCES = \
    OpenWBEM_Adapter.cpp \
    Converter.cpp  

LIBRARIES = \
    owprovider \
    owcppprovifc \
    openwbem \
    $(CIMPLE_LIBRARY_PREFIX)cimple$(CIMPLE_LIBRARY_SUFFIX)

include $(TOP)/mak/rules.mak

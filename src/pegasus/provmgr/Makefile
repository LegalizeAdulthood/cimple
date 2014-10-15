ROOT = $(PEGASUS_ROOT)
DIR = cimple/provmgr
include $(ROOT)/mak/config.mak

LIBRARY = cimpleprovmgr

SOURCES = \
    Subscription.cpp \
    Converter.cpp \
    CStr.cpp \
    CIMPLE_Provider_Manager.cpp

LIBRARIES = \
    pegprovidermanager \
    pegprovider \
    pegcommon \
    cimpledisp \
    cimple

CIMPLE_ROOT = ../../..
include $(CIMPLE_ROOT)/mak/extras.mak

include $(ROOT)/mak/library.mak

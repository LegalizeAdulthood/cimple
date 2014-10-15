ROOT = $(PEGASUS_ROOT)
DIR = cimple/adapater
include $(ROOT)/mak/config.mak

LIBRARY = cimplepegadap

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

SOURCES = \
    Pegasus_Thread_Context.cpp \
    Pegasus_Adapter.cpp \
    Converter.cpp \
    CStr.cpp

LIBRARIES = \
    pegprm \
    pegprovidermanager \
    pegprovider \
    pegconfig \
    pegcommon \
    cimple

INCLUDES += 

CIMPLE_ROOT = ../../..

include $(CIMPLE_ROOT)/mak/extras.mak
include $(ROOT)/mak/library.mak

genclass:

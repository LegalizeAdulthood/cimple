ROOT = $(PEGASUS_ROOT)
DIR = cimple/adapater
include $(ROOT)/mak/config.mak

LIBRARY = cimplepegadap

SOURCES = \
    Pegasus_Thread_Context.cpp \
    Pegasus_Adapter.cpp \
    Converter.cpp \
    CStr.cpp

LIBRARIES = \
    pegprovidermanager \
    pegprovider \
    pegcommon \
    cimple

INCLUDES += 

CIMPLE_ROOT = ../../..

include $(CIMPLE_ROOT)/mak/extras.mak
include $(ROOT)/mak/library.mak

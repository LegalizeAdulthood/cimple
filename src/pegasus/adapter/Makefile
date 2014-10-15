ROOT = $(PEGASUS_ROOT)
DIR = cimple/adapater
include $(ROOT)/mak/config.mak

LIBRARY = pegadap

SOURCES = \
    Pegasus_Adapter.cpp \
    Converter.cpp \
    CStr.cpp \
    Lamp.cpp \
    Lamp_Provider.cpp \
    main.cpp

LIBRARIES = \
    pegprovidermanager \
    pegprovider \
    pegcommon \
    cmplrep \
    cimple

INCLUDES += 

CIMPLE_ROOT = ../../..

include $(CIMPLE_ROOT)/mak/extras.mak
include $(ROOT)/mak/library.mak

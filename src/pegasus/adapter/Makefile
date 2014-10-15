TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimplepegadap

SOURCES = \
    Pegasus_Adapter.cpp \
    Pegasus_Thread_Context.cpp \
    pegasus_unsupported.cpp

LIBRARIES = \
    cimplepegutils \
    cimple \
    pegprm \
    pegprovidermanager \
    pegprovider \
    pegconfig \
    pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak
include ../check-pegasus.mak

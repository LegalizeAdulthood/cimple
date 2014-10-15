# ATTN: This is dangerous to mix debug Pegasus builds with non debug builds.
#ifdef CIMPLE_DEBUG
#  export PEGASUS_DEBUG=1
#endif

ROOT = $(PEGASUS_ROOT)
DIR = cimple/adapater
include $(ROOT)/mak/config.mak

LIBRARY = $(CIMPLE_LIBRARY_PREFIX)cimplepegadap$(CIMPLE_LIBRARY_SUFFIX)

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY -DCIMPLE_PEGADAP_INTERNAL

SOURCES = \
    Pegasus_Thread_Context.cpp \
    Pegasus_Adapter.cpp \
    Converter.cpp \
    pegasus_unsupported.cpp

LIBRARIES = \
    pegprm \
    pegprovidermanager \
    pegprovider \
    pegconfig \
    pegcommon \
    $(CIMPLE_LIBRARY_PREFIX)cimple$(CIMPLE_LIBRARY_SUFFIX)

INCLUDES += 

CIMPLE_ROOT = ../../..

include $(CIMPLE_ROOT)/mak/extras.mak
include $(ROOT)/mak/library.mak

genclass:

chksrc:
	chksrc $(SOURCES)

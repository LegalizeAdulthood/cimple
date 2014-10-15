TOP = ../../..
include $(TOP)/mak/config.mak
include $(TOP)/mak/pegasus.mak

SH_LIBRARY = cimpleprovmgr

SOURCES = \
    Subscription.cpp \
    Converter.cpp \
    CStr.cpp \
    CIMPLE_Provider_Manager.cpp

LINK_FLAGS += -L$(PEGASUS_HOME)/lib

LIBRARIES = \
    -lpegprovidermanager \
    -lpegprovider \
    -lpegcommon \
    -lcimpledisp \
    -lcimple \
    -lpthread

include $(TOP)/mak/rules.mak

tests:

dlopen:
	$(BIN)/dlopen $(TARGET)

genclass:

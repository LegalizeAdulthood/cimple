TOP = ../../../..
include $(TOP)/mak/config.mak
include $(TOP)/mak/pegasus.mak

BINARY = loadpm

SOURCES = loadpm.cpp

LINK_FLAGS += -L$(PEGASUS_HOME)/lib

LIBRARIES = \
    -lcimpleprovmgr \
    -lcimpleutil \
    -lpegprovidermanager \
    -lpegprovider \
    -lpegcommon \
    -lcimpledisp \
    -lcimple \
    -lpthread

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) $(LIB)/libcimpleprovmgr.so

genclass:

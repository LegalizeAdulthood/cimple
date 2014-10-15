TOP = ../../..
include $(TOP)/mak/config.mak
include $(TOP)/mak/pegasus.mak

SH_LIBRARY = pegcli

SOURCES = Client.cpp

LINK_FLAGS += -L$(PEGASUS_HOME)/lib

LIBRARIES = -lpegclient -lpegcommon -lcimple

FLAGS += -fno-enforce-eh-specs

include $(TOP)/mak/rules.mak

tests:

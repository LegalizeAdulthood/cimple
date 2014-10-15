TOP = ../../..
include $(TOP)/mak/config.mak

## Remove the comment on the INSTALL variable assignment to install
## this utility
#INSTALL=1

BINARY = cimlisten

SOURCES = main.cpp

LIBRARIES = \
    cimplepegutils \
    cimpleutil \
    cimple \
    pegclient \
    peglistener \
    pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak
include ../check-pegasus.mak

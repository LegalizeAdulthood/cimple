TOP = ../../..
include $(TOP)/mak/config.mak

## Remove the comment on the install varaible below to install this
## utility with the cimple make install
INSTALL=1

BINARY = ciminvoke

SOURCES = main.cpp 

LIBRARIES = pegclient pegcommon cimple

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak
include ../check-pegasus.mak

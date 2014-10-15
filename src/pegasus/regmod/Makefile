TOP = ../../..
include $(TOP)/mak/config.mak
include $(TOP)/mak/pegasus.mak

BINARY = regmod

SOURCES = main.cpp

LIBRARIES = \
    -lcimpleutil \
    -lcimple \
    -lpegprovider \
    -lpegrepository \
    -lpegcommon \
    -lpthread

DEFINES += -DPEGASUS_INTERNALONLY

include $(TOP)/mak/rules.mak

usage:
	file2c usage.txt -n USAGE > usage.h

tests:

genclass:


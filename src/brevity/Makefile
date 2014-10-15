TOP = ../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = brevity

SOURCES = \
    Client.cpp \
    Instance_Enum.cpp \
    Instance_Name_Enum.cpp

LIBRARIES = cimplepegutils cimple pegclient pegcommon

DEFINES += -DCIMPLE_BUILDING_BREVITY

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

INSTALL_HEADERS_DIR = brevity

INSTALL_HEADERS = $(wildcard *.h)

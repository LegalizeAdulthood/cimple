TOP = ../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimpleutil

SOURCES = \
    util.cpp \
    crc.cpp \
    MAC.cpp \
    UUID.cpp

LIBRARIES =

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLEUTIL_INTERNAL

include $(TOP)/mak/rules.mak

tests:

genclass:

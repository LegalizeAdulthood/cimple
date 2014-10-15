TOP = ../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cimpleutil
STATIC_LIBRARY = cimpleutil_s

SOURCES = \
    util.cpp \
    crc.cpp \
    UUID.cpp \
    MAC.cpp

LIBRARIES =

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLEUTIL_INTERNAL

include $(TOP)/mak/rules.mak

tests:

genclass:

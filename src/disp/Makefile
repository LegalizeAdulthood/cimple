TOP = ../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cimpledisp

SOURCES = \
    version.cpp \
    Buffer.cpp \
    Cache.cpp \
    Cache_IO.cpp \
    Dispatcher.cpp \
    Dispatcher_IO.cpp \
    DZT_String.cpp \
    Envelope.cpp \
    Facade.cpp \
    Facade_IO.cpp \
    Files.cpp \
    Module.cpp \
    Module_IO.cpp \
    Repository.cpp \
    State.cpp \
    Status.cpp

LIBRARIES = cimple

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLEDISP_INTERNAL

include $(TOP)/mak/rules.mak

genclass:

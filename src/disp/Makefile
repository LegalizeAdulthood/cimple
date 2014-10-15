TOP = ../..
include $(TOP)/mak/config.mak

LIBRARY = cimpledisp

SOURCES = \
    Buffer.cpp \
    Cache.cpp \
    Cache_IO.cpp \
    Dispatcher.cpp \
    Dispatcher_IO.cpp \
    DZT_String.cpp \
    Envelope.cpp \
    Error.cpp \
    Facade.cpp \
    Facade_IO.cpp \
    Files.cpp \
    Module.cpp \
    Module_IO.cpp \
    Repository.cpp \
    State.cpp \
    Status.cpp

LIBRARIES = -lcimple -ldl -lpthread

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLE_LIBCIMPLE_INTERNAL

include $(TOP)/mak/rules.mak

genclass:

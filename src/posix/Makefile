TOP = ../..
POSIX_MAKEFILE=1
include $(TOP)/mak/config.mak

SH_LIBRARY = posix

SOURCES = \
    dirent.cpp \
    dlfcn.cpp  \
    getopt.cpp \
    unistd.cpp \
    libgen.cpp \
    pthread.cpp \
    time.cpp

LIBRARIES =

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DPOSIX_INTERNAL

include $(TOP)/mak/rules.mak

genclass:

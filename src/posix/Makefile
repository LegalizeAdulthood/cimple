TOP = ../..
POSIX_MAKEFILE=1
include $(TOP)/mak/config.mak

STATIC_LIBRARY = cimpleposix

INSTALL=1

SOURCES = \
    dirent.cpp \
    dlfcn.cpp  \
    getopt.cpp \
    unistd.cpp \
    libgen.cpp \
    pthread.cpp \
    time.cpp

DEFINES += -DPOSIX_INTERNAL

include $(TOP)/mak/rules.mak

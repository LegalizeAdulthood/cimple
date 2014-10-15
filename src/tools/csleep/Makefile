TOP = ../../..
include $(TOP)/mak/config.mak

## install only on windows platforms.  Used by
## make world
ifdef CIMPLE_WINDOWS_MSVC
INSTALL=1
endif

BINARY = csleep
SOURCES = main.cpp
LIBRARIES =

include $(TOP)/mak/rules.mak

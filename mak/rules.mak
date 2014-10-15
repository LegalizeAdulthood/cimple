ifdef LIBRARY
OBJECTS = $(SOURCES:.cpp=.o)
include $(TOP)/mak/lib.mak
include $(TOP)/mak/object.mak
include $(TOP)/mak/clean.mak
include $(TOP)/mak/depend.mak
endif

ifdef SH_LIBRARY
OBJECTS = $(SOURCES:.cpp=.o)
include $(TOP)/mak/shlib.mak
include $(TOP)/mak/object.mak
include $(TOP)/mak/clean.mak
include $(TOP)/mak/depend.mak
endif

ifdef BINARY
OBJECTS = $(SOURCES:.cpp=.o)
include $(TOP)/mak/bin.mak
include $(TOP)/mak/object.mak
include $(TOP)/mak/clean.mak
include $(TOP)/mak/depend.mak
endif

ifdef DIRS
include $(TOP)/mak/dir.mak
endif

TOP = $(HOME)/cimple
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cim211

SOURCES = $(shell ls *.cpp)

LIBRARIES = cimple

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLE_INTERNAL

include $(TOP)/mak/rules.mak

genclass:
	genclass -s -r -l

CLEAN += $(SOURCES)

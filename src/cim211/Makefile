TOP = ../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim211

SHARED_LIBRARY = cim211

SOURCES = $(shell ls *.cpp)

LIBRARIES = cimple

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLE_INTERNAL

include $(TOP)/mak/rules.mak

genclass:
	genclass -r -s

genclass-full:
	genclass -q -s -r -l

CLEAN += $(SOURCES) $(SOURCES:.cpp=.h)

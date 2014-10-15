
ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifndef CC
  CC = gcc
endif

FLAGS = -Wall -Wno-unused
#FLAGS += -Wswitch-enum -fPIC -Wno-unused-label

ifdef CIMPLE_TREAT_WARNINGS_LIKE_ERRROS
FLAGS += -Werror
endif

SIZE_OPTIMIZATION_FLAGS = -fno-rtti -fno-exceptions

ifdef CIMPLE_DEBUG
    FLAGS += -g -DCIMPLE_DEBUG
else
    FLAGS += -Os
endif

FLAGS += -fPIC

DEFINES = -D_GNU_SOURCE
INCLUDES = -I$(TOP)/src
VALGRIND = valgrind --tool=memcheck --alignment=8 --leak-check=yes

AR_OPTS = rv

ifdef PEGASUS_HOME
 BIN = $(shell mkdir -p $(PEGASUS_HOME)/bin; cd $(PEGASUS_HOME)/bin; pwd)
 LIB = $(shell mkdir -p $(PEGASUS_HOME)/lib; cd $(PEGASUS_HOME)/lib; pwd)
else
 BIN = $(shell mkdir -p $(TOP)/bin; cd $(TOP)/bin; pwd)
 LIB = $(shell mkdir -p $(TOP)/lib; cd $(TOP)/lib; pwd)
endif

SRC = $(shell cd $(TOP)/src; pwd)

#export LD_LIBRARY_PATH=$(LIB)

LINK_FLAGS += -L$(LIB)

#FLAGS += -fno-rtti -fno-exceptions

CONFIG_MAK = 1

define NEWLINE


endef

ifndef CIMPLE_MOF_PATH
export CIMPLE_MOF_PATH = $(shell cd $(TOP)/schema; pwd)
endif

RPATH_OPT = -Wl,-rpath=$(LIB)

-include $(TOP)/mak/defines.mak

#STATIC_LIBSTDCXX=$(shell $(CXX) --print-file-name=libstdc++.a)

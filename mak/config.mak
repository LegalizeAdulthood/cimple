##==============================================================================
##
## Check CIMPLE_PLATFORM definition.
##
##==============================================================================

CIMPLE_PLATFORM=
-include $(TOP)/mak/platform.mak

ifeq ($(CIMPLE_PLATFORM),)
  $(error "First type ./configure")
endif

include $(TOP)/mak/platform_$(CIMPLE_PLATFORM).mak

##==============================================================================
##
## Be sure TOP refers to an actual directory
##
##==============================================================================

ifeq ($(wildcard $(TOP)),)
    $(error "TOP does not refer to a legal directory)
endif

##==============================================================================
##
## CIMPLE_ROOT
##
##==============================================================================

CIMPLE_ROOT = $(call abs_path, $(TOP))

##==============================================================================
##
## BIN, LIB & SRC
##
##     If PEGASUS_HOME is defined, programs and libraries are placed under
##     that directory.
##
##==============================================================================

ifdef PEGASUS_HOME
  BIN = $(PEGASUS_HOME)/bin
  LIB = $(PEGASUS_HOME)/lib
else
  BIN = $(CIMPLE_ROOT)/bin
  LIB = $(CIMPLE_ROOT)/lib
endif

SRC = $(CIMPLE_ROOT)/src

ifdef CIMPLE_WINDOWS
  SHLIB = $(BIN)
else
  SHLIB = $(LIB)
endif

##==============================================================================
##
## CIMPLE_MOF_PATH
##
##==============================================================================

ifndef CIMPLE_MOF_PATH
  export CIMPLE_MOF_PATH = $(TOP)/schema
endif

##==============================================================================
##
## INCLUDES
##
##==============================================================================

INCLUDES += -I$(TOP)/src

##==============================================================================
##
## NL - newline macro
##
##==============================================================================

define NL


endef

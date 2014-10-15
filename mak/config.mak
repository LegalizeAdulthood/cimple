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
## CIMPLE_DEBUG
##
##==============================================================================

ifdef PEGASUS_HOME
  ifdef PEGASUS_DEBUG
    export CIMPLE_DEBUG=1
  endif
endif

ifdef CIMPLE_DEBUG
  DEFINES += -DCIMPLE_DEBUG
endif

##==============================================================================
##
## BIN_DIR, LIB_DIR & SRC_DIR
##
##     If PEGASUS_HOME is defined, programs and libraries are placed under
##     that directory.
##
##==============================================================================

ifdef PEGASUS_HOME
  BIN_DIR = $(PEGASUS_HOME)/bin
  LIB_DIR = $(PEGASUS_HOME)/lib
else
  BIN_DIR = $(CIMPLE_ROOT)/bin
  LIB_DIR = $(CIMPLE_ROOT)/lib
endif

SRC_DIR = $(CIMPLE_ROOT)/src

ifdef CIMPLE_WINDOWS
  SHLIB = $(BIN_DIR)
else
  SHLIB = $(LIB_DIR)
endif

##==============================================================================
##
## CIMPLE_SCHEMA_PATH
##
##     Location of schema to be used by various programs.
##
##==============================================================================

ifndef CIMPLE_SCHEMA_PATH
    CIMPLE_SCHEMA_PATH=$(TOP)/schema/cim211
endif

##==============================================================================
##
## CIMPLE_MOF_PATH
##
##     Used by genclass and genprov utilities to find MOF files.
##
##==============================================================================

ifndef CIMPLE_MOF_PATH
  export CIMPLE_MOF_PATH=$(CIMPLE_SCHEMA_PATH)
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

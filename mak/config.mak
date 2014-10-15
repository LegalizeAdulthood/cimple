.PHONY: all 
.PHONY: depend 
.PHONY: clean 
.PHONY: tests
.PHONY: gen
.PHONY: sub
.PHONY: genclass
.PHONY: genprov
.PHONY: genmod
.PHONY: regmod
.PHONY: chksrc
.PHONY: live
.PHONY: install
.PHONY: uninstall
.PHONY: insmod
.PHONY: rmmod
.PHONY: vars
.PHONY: vg

##==============================================================================
##
## Include config.options file.
##
##==============================================================================

PLATFORM=
-include $(TOP)/config.options

ifeq ($(PLATFORM),)
  $(error "No configuration setup. Type ./configure to set configuration")
endif

##==============================================================================
##
## Fixups for Windows configure.
##
##==============================================================================

ifdef WIN_ENABLE_DEBUG_OPT
  ENABLE_DEBUG_OPT=1
endif

ifdef WIN_ENABLE_STATIC_OPT
  ENABLE_STATIC_OPT=1
endif

ifdef WIN_ENABLE_EMBEDDED_INSTANCES_OPT
  ENABLE_EMBEDDED_INSTANCES_OPT=1
endif

ifdef WIN_ENABLE_SCHEDULER_OPT
  ENABLE_SCHEDULER_OPT=1
endif

ifdef WIN_ENABLE_ADAPTER_TRACE_OPT
  ENABLE_ADAPTER_TRACE_OPT
endif

##==============================================================================
##
## Include platform file.
##
##==============================================================================
link_targets =
include $(TOP)/mak/platform_$(PLATFORM).mak

##==============================================================================
##
## CMPI_VOID_RETURN_BUG_OPT
##
##==============================================================================

ifneq ($(WITH_CMPI_OPT),)

  ifneq ($(call grep,void.*enableIndications,$(WITH_CMPI_OPT)/cmpift.h),)
    CMPI_VOID_RETURN_BUG_OPT=1
  endif

endif

##==============================================================================
##
## Find cimcli
##
##==============================================================================

ifneq ($(WITH_PEGASUS_OPT),)

  ifeq ($(CIMCLI),)
    CIMCLI=$(wildcard $(WITH_PEGASUS_OPT)/bin/CLI)
  endif

  ifeq ($(CIMCLI),)
    CIMCLI=$(wildcard $(WITH_PEGASUS_OPT)/bin/cimcli)
  endif

  ifeq ($(CIMCLI),)
    CIMCLI=$(wildcard $(WITH_PEGASUS_OPT)/sbin/CLI)
  endif

  ifeq ($(CIMCLI),)
    CIMCLI=$(wildcard $(WITH_PEGASUS_OPT)/sbin/cimcli)
  endif

  ifeq ($(CIMCLI),)
    CIMCLI=$(wildcard $(WITH_PEGASUS_OPT)/bin/CLI.exe)
  endif

  ifeq ($(CIMCLI),)
    CIMCLI=$(wildcard $(WITH_PEGASUS_OPT)/bin/cimcli.exe)
  endif


endif

##==============================================================================
##
## Set common name for Makefile SLEEP command
##
##==============================================================================

ifeq ($(PEGASUS_PLATFORM),WIN32_IX86_MSVC)
  SLEEP = ./bin/csleep
else
  SLEEP = sleep
endif

##==============================================================================
##
## Define Valgrind Location for some test commands that use Valgrind
## This is primarily developer test
##
##==============================================================================

ifndef VALGRIND
  VALGRIND=valgrind
endif

##==============================================================================
##
## Define several make variables to allow the Makefiles to be platform
## independent.  Any of these may be overridden in platform make files
## However, in general, the platform files alais the right hand side (ex rm)
##
##==============================================================================

ifndef DIFF
  DIFF = diff
endif

ifndef RM
  RM = rm
endif

ifndef RMDIRHIER
  RMDIRHIER = rm -rf
endif

ifndef COPY
  COPY = cp
  CP = cp
endif

ifndef CUT
   CUT = cut
endif

##==============================================================================
##
## ENABLE_DEBUG_OPT - Set corresponding compile flag
##
##==============================================================================

ifdef ENABLE_DEBUG_OPT
  DEFINES += -DCIMPLE_DEBUG
endif

##==============================================================================
##
## Be sure TOP refers to an actual directory
##
##==============================================================================

ifeq ($(wildcard $(TOP)),)
  $(error "TOP does not refer to a legal directory")
endif

##==============================================================================
##
## ROOT
##
##==============================================================================

ifndef CIMPLE_ROOT
  CIMPLE_ROOT = $(call abs_path, $(TOP))
endif

##==============================================================================
##
## BINDIR
##
##==============================================================================

ifndef BINDIR
  BINDIR = $(CIMPLE_ROOT)/bin
endif

##==============================================================================
##
## LIBDIR
##
##==============================================================================

ifndef LIBDIR
  LIBDIR = $(CIMPLE_ROOT)/$(LIBBASE_OPT)
endif

##==============================================================================
##
## SRC_DIR
##
##==============================================================================

SRC_DIR = $(CIMPLE_ROOT)/src

##==============================================================================
##
## SHLIB
##
##==============================================================================

ifdef CIMPLE_WINDOWS
  SHLIB = $(BINDIR)
else
  SHLIB = $(LIBDIR)
endif

##==============================================================================
##
## INCLUDES
##
##==============================================================================

INCLUDES += -I$(TOP)/src 
INCLUDES += -I$(TOP)/src/stdincludes/$(PLATFORM)
INCLUDES += -I$(INCLUDEDIR_OPT)

##==============================================================================
##
## NL - newline macro
##
##==============================================================================

define NL


endef

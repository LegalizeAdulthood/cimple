##==============================================================================
##
## extras.mak
##
##     This makefile defines additional definitions for using the Pegasus
##     make system with CIMPLE headers.
##
##==============================================================================

ifndef CIMPLE_ROOT
  $(error "please define CIMPLE_ROOT before including this file)
endif

include $(CIMPLE_ROOT)/mak/platform.mak

EXTRA_INCLUDES += -I$(CIMPLE_ROOT)/src

ifeq ($(CIMPLE_PLATFORM),WIN32_IX86_MSVC)
  EXTRA_INCLUDES += -I$(CIMPLE_ROOT)/src/posix
  LIBRARIES += posix
endif

ifneq ($(CIMPLE_PLATFORM),$(PEGASUS_PLATFORM))
  $(error "CIMPLE_PLATFORM ($(CIMPLE_PLATFORM)) does not match \
    PEGASUS_PLATFORM ($(PEGASUS_PLATFORM))")
endif

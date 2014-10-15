TOP = ..
include $(TOP)/mak/config.mak

DIRS += options

ifdef CIMPLE_WINDOWS
  DIRS += posix
  DIRS += posix/tests
endif

DIRS += \
    mof \
    mof/mofc \
    mof/tests \
    cimple \
    util \
    tools \
    cimple/tests

ifneq ($(WITH_PEGASUS_OPT),)
    DIRS += pegasus
endif

ifneq ($(WITH_CMPI_OPT),)
    DIRS += cmpi
endif

ifneq ($(WITH_OPENWBEM_OPT),)
    DIRS += openwbem
endif

ifneq ($(WITH_PEGASUS_OPT),)
  ifneq ($(WITH_CMPI_OPT),)
    DIRS += providers
  endif
endif

include $(TOP)/mak/dir.mak

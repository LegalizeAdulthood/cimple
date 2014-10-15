TOP = ..
include $(TOP)/mak/config.mak

DIRS += options

ifeq ($(PLATFORM),VXWORKS_XSCALE_GNU)

  DIRS += cimple
  DIRS += pegasus/utils
  DIRS += pegasus/adapter

else

  ifdef CIMPLE_WINDOWS
    DIRS += posix
    DIRS += posix/tests
  endif

  DIRS += mof
  DIRS += mof/mofc
  DIRS += mof/tests
  DIRS += cimple
  DIRS += util
  DIRS += tools
  DIRS += cimple/tests

  ifneq ($(WITH_PEGASUS_OPT),)
      DIRS += pegasus
  endif

  ifneq ($(WITH_CMPI_OPT),)
      DIRS += cmpi
  endif

  ifneq ($(WITH_OPENWBEM_OPT),)
      DIRS += openwbem
  endif

  ifeq ($(ENABLE_WMI_OPT),TRUE)
    DIRS += wmi
  endif

  ifneq ($(WITH_PEGASUS_OPT),)
    ifneq ($(WITH_CMPI_OPT),)
      DIRS += providers
    endif
  endif

ifneq ($(WITH_PEGASUS_OPT),)
    DIRS += brevity
    DIRS += brevity/tests
endif

endif

include $(TOP)/mak/dir.mak

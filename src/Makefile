TOP = ..
include $(TOP)/mak/config.mak

ifdef CIMPLE_WINDOWS
  DIRS += posix
  DIRS += posix/tests
endif

DIRS += \
    tools/dlopen \
    mof \
    mof/mofc \
    mof/mof2html \
    mof/tests \
    cimple \
    cimple/tests \
    disp \
    disp/tests \
    util \
    tools \
    cimple/tests

ifdef PEGASUS_HOME
    DIRS += pegasus
    DIRS += cmpi
    DIRS += providers
endif

include $(TOP)/mak/dir.mak

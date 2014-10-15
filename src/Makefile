TOP = ..
include $(TOP)/mak/config.mak

ifdef CIMPLE_WINDOWS
  DIRS += posix
  DIRS += posix/tests
endif

DIRS += \
    tools/dlopen \
    cimple \
    disp \
    mof \
    mof/mofc \
    mof/mof2html \
    mof/tests \
    util \
    tools \
    disp/tests \
    cimple/tests \
    providers/repository \
    providers/Person2

ifdef PEGASUS_HOME
    DIRS += pegasus
    DIRS += cmpi
    DIRS += providers
endif

include $(TOP)/mak/dir.mak

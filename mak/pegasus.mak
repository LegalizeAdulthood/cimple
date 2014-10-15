##------------------------------------------------------------------------------
##
## PEGASUS_ROOT
##
##------------------------------------------------------------------------------

ifndef PEGASUS_ROOT
pegasus_root_undefined:
	@ echo "Error: PEGASUS_ROOT is undefined"
endif

INCLUDES += -I$(PEGASUS_ROOT)/src

##------------------------------------------------------------------------------
##
## PEGASUS_HOME
##
##------------------------------------------------------------------------------

ifndef PEGASUS_HOME
pegasus_home_undefined:
	@ echo "Error: PEGASUS_HOME is undefined"
endif

##------------------------------------------------------------------------------
##
## PEGASUS_PLATFORM
##
##------------------------------------------------------------------------------

ifndef PEGASUS_PLATFORM
pegasus_platform_undefined:
	@ echo "Error: PEGASUS_PLATFORM is undefined"
else
FLAGS += -DPEGASUS_PLATFORM_LINUX_GENERIC_GNU
FLAGS += -DPEGASUS_PLATFORM_$(PEGASUS_PLATFORM)
endif

##------------------------------------------------------------------------------
##
## PEGASUS_DEBUG
##
##------------------------------------------------------------------------------

ifdef PEGASUS_DEBUG
  FLAGS += -DPEGASUS_DEBUG
else
  ifneq ($(PEGASUS_PLATFORM), LINUX_PPC_GNU)
    FLAGS += -fno-enforce-eh-specs
  endif
endif

##------------------------------------------------------------------------------
##
## LD_LIBRARY_PATH
##
##------------------------------------------------------------------------------

export LD_LIBRARY_PATH=$(LIB):$(PEGASUS_HOME)/lib
LINK_FLAGS += -L$(PEGASUS_HOME)/lib -lpthread -ldl

DEFINES += -D_REENTRANT
DEFINES += -DTHREAD_SAFE
DEFINES += -D_GNU_SOURCE
DEFINES += -DPEGASUS_USE_EXPERIMENTAL_INTERFACES
DEFINES += -DPEGASUS_USE_DEPRECATED_INTERFACES
DEFINES += -Wno-unused
DEFINES += -DPEGASUS_INTERNALONLY
DEFINES += -DPEGASUS_USE_ARRAY_INLINE

##------------------------------------------------------------------------------
##
## CMPI_INCLUDES (for Pegasus only)
##
##------------------------------------------------------------------------------

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

ifeq ($(PEGASUS_PLATFORM), LINUX_PPC_GNU)
  RPATH_OPT = -Wl,-rpath-link=$(LIB)
endif

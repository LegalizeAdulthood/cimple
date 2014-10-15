TOP = ../../..
include $(TOP)/mak/config.mak
include cmpi.mak

ifdef STATIC
  STATIC_LIBRARY = cimplecmpiadap_s
  DEFINES += -DCIMPLE_CIMPLE_LINKAGE=""
  LIBRARIES = cimple_s
else
  SHARED_LIBRARY = cimplecmpiadap
  LIBRARIES = cimple
endif

SOURCES = \
    CMPI_Thread_Context.cpp \
    Converter.cpp \
    CMPI_Adapter.cpp \

DEFINES += -DCIMPLE_NEED_CMPI_IO
DEFINES += -DCIMPLECMPL_INTERNAL

ifdef CMPI_ROOT
    INCLUDES += -I$(CMPI_ROOT)
else
    $(error "please define CMPI_ROOT to point to CMPI include directory")
endif

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

genclass:

##==============================================================================
##
## static
##
##     This rule builds a static adapter library (named cimplecmpiadap_s).
##
##==============================================================================

static:
	$(MAKE) clean
	$(MAKE) STATIC=1

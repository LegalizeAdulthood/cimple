TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplbug31

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

SOURCES = \
    BUG31_C_Provider.cpp \
    BUG31_A.cpp \
    BUG31_B.cpp \
    BUG31_C.cpp \
    repository.cpp \
    module.cpp

LIBRARIES = cimple

BUILD_CMPI_PROVIDER=1
ifdef BUILD_CMPI_PROVIDER
  LIBRARIES += cimplecmpiadap
  DEFINES += -DBUILD_CMPI_PROVIDER
else
  LIBRARIES += cimplepegadap
endif

include $(TOP)/mak/rules.mak

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:

genclass:
	genclass -r BUG31_A BUG31_B BUG31_C

genprov:
	genprov -f BUG31_C

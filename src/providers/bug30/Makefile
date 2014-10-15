TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplbug30

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

SOURCES = \
    BUG30_X_Provider.cpp \
    BUG30_R.cpp \
    BUG30_S.cpp \
    BUG30_X.cpp \
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
	genclass -r BUG30_X BUG30_S

genprov:
	genprov -f BUG30_X

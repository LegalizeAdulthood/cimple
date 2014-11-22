TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplbug30

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

GENCLASS_SOURCES = \
    BUG30_R.cpp \
    BUG30_S.cpp \
    BUG30_X.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    BUG30_X_Provider.cpp \
    module.cpp

LIBRARIES = cimple

BUILD_CMPI_PROVIDER=1
ifdef BUILD_CMPI_PROVIDER
  LIBRARIES += cimplecmpiadap
  DEFINES += -DBUILD_CMPI_PROVIDER
else
  LIBRARIES += cimplepegadap
endif

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

reg:
	$(BINDIR)/regmod -c $(SHARED_LIBRARY_TARGET)

tests:

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r BUG30_X BUG30_S

genprov:
	$(BINDIR)/genprov -f BUG30_X

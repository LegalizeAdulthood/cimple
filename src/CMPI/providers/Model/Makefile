TOP = ../../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = ModelProvider

GENCLASS_SOURCES = \
    Model.cpp \
    Part.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    Model_Provider.cpp \
    module.cpp

LIBRARIES = cimplecmpi cmplrep cimple

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

INCLUDES += $(CMPI_INCLUDES) -I$(TOP)/src/CMPI/cmpi

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

ifdef CIMPLE_WINDOWS
   DEFINES += -DCMPI_PLATFORM_WIN32_IX86_MSVC
endif


include $(TOP)/mak/rules.mak

reg:
	regmod -c -m $(TARGET)

repository.mof: Model.mof
genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass Model Part

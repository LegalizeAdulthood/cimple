TOP = ../../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Benchmark3Provider

SOURCES = \
    Benchmark3.cpp \
    CIM_Card.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_PhysicalConnector.cpp \
    CIM_PhysicalElement.cpp \
    CIM_PhysicalPackage.cpp \
    Benchmark3_Provider.cpp \
    module.cpp \
    repository.cpp

#LIBRARIES = cimple cimplecmpiadap
LIBRARIES = cimple cimplepegadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

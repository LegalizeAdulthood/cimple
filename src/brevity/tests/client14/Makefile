TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_client13

GENCLASS_SOURCES = \
    CIM_ConcreteJob.cpp \
    CIM_CoolingDevice.cpp \
    CIM_ElementConformsToProfile.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Fan.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_RegisteredProfile.cpp \
    repository.cpp

SOURCES = $(GENCLASS_SOURCES) $(wildcard *.cpp)

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

CLASSES = CIM_RegisteredProfile CIM_Fan CIM_ElementConformsToProfile

gen $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -r $(CLASSES)
	$(BINDIR)/genhnd $(CLASSES)

publish:

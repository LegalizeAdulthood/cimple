TOP = ../../../..
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

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

GENHND_HEADERS = $(GENCLASS_SOURCES:.cpp=_Hnd.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS) $(GENHND_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

CLASSES = CIM_RegisteredProfile CIM_Fan CIM_ElementConformsToProfile

gen $(GENCLASS_SOURCES) $(GENHND_HEADERS):
	$(BINDIR)/genclass -r $(CLASSES)
	$(BINDIR)/genhnd $(CLASSES)

publish:

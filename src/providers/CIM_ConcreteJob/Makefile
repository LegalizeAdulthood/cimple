TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimple_CIM_ConcreteJob

INCLUDES += $(CMPI_INCLUDES)

GENERATED_SOURCES = \
    CIM_ConcreteJob.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    repository.cpp

SOURCES = \
    $(GENERATED_SOURCES) \
    CIM_ConcreteJob_Provider.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

$(GENERATED_SOURCES):
	$(BINDIR)/genclass -r CIM_ConcreteJob

genclass:
	$(BINDIR)/genclass -r CIM_ConcreteJob

genprov:
	$(BINDIR)/genprov CIM_ConcreteJob

genmod:
	$(BINDIR)/genmod CIM_ConcreteJob CIM_ConcreteJob

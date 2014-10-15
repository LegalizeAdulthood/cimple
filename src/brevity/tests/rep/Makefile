TOP = ../../../..
include $(TOP)/mak/config.mak

STATIC_LIBRARY = brevityrep

SOURCES = \
    All_Class.cpp \
    All_Part.cpp \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_IndicationFilter.cpp \
    CIM_IndicationHandlerCIMXML.cpp \
    CIM_IndicationHandler.cpp \
    CIM_IndicationSubscription.cpp \
    CIM_Job.cpp \
    CIM_ListenerDestination.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    Employee.cpp \
    Link.cpp \
    Manager.cpp \
    OutOfOfficeNotice.cpp \
    repository.cpp

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:

CLASSES = \
    Employee \
    Manager \
    Link \
    OutOfOfficeNotice \
    All_Part \
    All_Class \
    CIM_IndicationSubscription \
    CIM_IndicationFilter \
    CIM_IndicationHandlerCIMXML \
    CIM_ComputerSystem

MOF1=$(TOP)/src/providers/Employee/repository.mof
MOF2=$(TOP)/src/providers/All/repository.mof

gen:
	$(BINDIR)/genclass -r -M $(MOF1) -M $(MOF2) $(CLASSES)
	$(BINDIR)/genhnd -M $(MOF1) -M $(MOF2) $(CLASSES)

publish:
	cp *.h /home/mbrasher/websites/www.cimple.org/brevity

TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleXYZ_Lamp

GENCLASS_SOURCES = \
    CIM_Indication.cpp \
    XYZ_Lamp.cpp \
    XYZ_LampIndic.cpp \
    XYZ_LampLink.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    XYZ_LampIndic_Provider.cpp \
    XYZ_LampLink_Provider.cpp \
    XYZ_Lamp_Provider.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r XYZ_Lamp XYZ_LampLink XYZ_LampIndic

genprov:
	$(BINDIR)/genprov XYZ_Lamp
	$(BINDIR)/genprov XYZ_LampLink
	$(BINDIR)/genprov XYZ_LampIndic

genmod:
	$(BINDIR)/genmod XYZ_Lamp XYZ_Lamp XYZ_LampLink XYZ_LampIndic


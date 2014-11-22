TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleLamp

GENCLASS_SOURCES = \
    CIM_Indication.cpp \
    Lamp.cpp \
    LampIndicA.cpp \
    LampIndicB.cpp \
    LampIndicC.cpp \
    LampIndic.cpp \
    LampLink.cpp \
    ModernLamp.cpp \
    Persistent.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    LampIndic_Provider.cpp \
    LampLink_Provider.cpp \
    Lamp_Provider.cpp \
    module.cpp

# Allow building providers for either CMPI or Pegasus C++ provider interface
# Changing Provider interfaces requires reregistering the provider. Default Pegasus
#
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/cimv2 -s -c $(TARGET)

regmodxyz:
	$(BINDIR)/regmod -n root/xyz -s -c $(TARGET)

genclass $(GENCLASS_SOURCES) $(GENCLASS_HEADERS): repository.mof
	$(BINDIR)/genclass -r Lamp ModernLamp LampLink LampIndic LampIndicA LampIndicB LampIndicC Persistent

genprov:
	$(BINDIR)/genprov Lamp
	$(BINDIR)/genprov LampIndic
	$(BINDIR)/genprov LampLink

genmod:
	$(BINDIR)/genmod Lamp Lamp LampIndic LampLink

live:
	$(CIMCLI) ei Lamp
	$(CIMCLI) gi 'Lamp.model="A"'
	$(CIMCLI) an 'Lamp.model="A"'
	$(CIMCLI) rn 'Lamp.model="A"'
	$(CIMCLI) a 'Lamp.model="A"'
	$(CIMCLI) r 'Lamp.model="A"'

test:
	$(CIMCLI) an 'Lamp.model="A"'

LampIndic_Provider.cpp: LampIndic_Provider.h
LampIndic_Provider.h: LampIndic.h

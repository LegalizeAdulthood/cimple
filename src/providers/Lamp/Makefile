TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleLamp

SOURCES = \
    CIM_Indication.cpp \
    Lamp.cpp \
    LampIndicA.cpp \
    LampIndicB.cpp \
    LampIndicC.cpp \
    LampIndic.cpp \
    LampIndic_Provider.cpp \
    LampLink.cpp \
    LampLink_Provider.cpp \
    Lamp_Provider.cpp \
    ModernLamp.cpp \
    Persistent.cpp \
    module.cpp \
    repository.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/cimv2 -s -c $(TARGET)

genclass:
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

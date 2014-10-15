TOP = ../../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = MyIndicationProvider

SOURCES = MyIndication_Provider.cpp module.cpp

LIBRARIES = -lcimplecmpi -lcmplrep -lcimple

REPOSITORY = $(TOP)/src/providers/repository

CMPI_INCLUDES = \
    -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

INCLUDES += $(CMPI_INCLUDES) -I$(TOP)/src/CMPI/cmpi -I$(REPOSITORY)

FLAGS += -fno-rtti -fno-exceptions

include $(TOP)/mak/rules.mak

reg:
	regmod -c -m $(TARGET)

genclass:
	genclass -I$(REPOSITORY) MyIndication

genprov:
	genprov -I$(REPOSITORY) MyIndication

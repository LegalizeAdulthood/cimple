TOP = ../../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = MyIndicationProvider

SOURCES = MyIndication_Provider.cpp module.cpp

LIBRARIES = cimplecmpi cmplrep cimple

REPOSITORY = $(TOP)/src/providers/repository

CMPI_INCLUDES = -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

INCLUDES += $(CMPI_INCLUDES) -I$(TOP)/src/CMPI/cmpi -I$(REPOSITORY)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

reg:
	regmod -c -m $(TARGET)

genclass:
	genclass -I$(REPOSITORY) MyIndication

genprov:
	genprov -I$(REPOSITORY) MyIndication

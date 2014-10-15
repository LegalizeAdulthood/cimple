TOP = ../../..
include $(TOP)/mak/config.mak

ifdef PEGASUS_HOME
include $(TOP)/mak/pegasus.mak
endif

INCLUDES += -I../repository

SH_LIBRARY = cmplcsdd

SOURCES = ComputerSystemDiskDrive_Provider.cpp module.cpp

LIBRARIES = -lcimple -lcmplrep

include $(TOP)/mak/rules.mak

FLAGS += -fno-rtti -fno-exceptions

reg:
	regmod -c $(TARGET)

genprov:
	genprov -I ../repository -f Example

genclass:
	genclass Example

tests:
	@ $(BIN)/dlopen $(TARGET)

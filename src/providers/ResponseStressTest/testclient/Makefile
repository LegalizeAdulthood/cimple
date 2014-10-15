TOP = ../../../..
include $(TOP)/mak/config.mak

## required because we use Pegasus Stopwatch function
LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

BINARY = TestResponseTestProvider

SOURCES = main.cpp

LIBRARIES = cimple cimplepegutils pegclient pegcommon peggeneral

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

live:
	$(TARGET)

## run test comparing this and pegasus provider
one:
	$(TARGET) one

## run test comparing this and pegasus provider
test:
	$(TARGET) test

TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = President
SOURCES = repository.cpp President.cpp module.cpp President_Provider.cpp
LIBRARIES = cimple cimplecmpiadap

include $(TOP)/mak/rules.mak

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

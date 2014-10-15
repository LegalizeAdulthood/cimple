TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = StringArrayProvider

SOURCES = \
    module.cpp \
    repository.cpp \
    StringArrayClass.cpp \
    StringArrayClass_Provider.cpp

DEFINES += -DCIMPLE_CMPI_MODULE
LIBRARIES += cimplecmpiadap cimple

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/cimv2 -s -c $(TARGET)

TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplemyindic

SOURCES = \
    CIM_Indication.cpp \
    module.cpp \
    MyEmbeddedClass.cpp \
    MyIndication.cpp \
    MyIndication_Provider.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

ifdef CIMPLE_WINDOWS_MSVC
    DEV_NULL=.dev.null
else
    DEV_NULL=/dev/null
endif

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r MyIndication MyEmbeddedClass

genprov:
	$(BINDIR)/genprov MyIndication

genmod:
	$(BINDIR)/genmod MyIndication MyIndication

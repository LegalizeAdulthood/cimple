TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplebug31

INCLUDES += $(CMPI_INCLUDES)

SOURCES = \
    BUG31_C_Provider.cpp \
    BUG31_A.cpp \
    BUG31_B.cpp \
    BUG31_C.cpp \
    repository.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r BUG31_A BUG31_B BUG31_C

genprov:
	$(BINDIR)/genprov BUG31_C

genmod:
	$(BINDIR)/genmod BUG31_C BUG31_C

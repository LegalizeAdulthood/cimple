TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleCross

SOURCES = \
    CMPL_Cross.cpp \
    CMPL_Cross_Provider.cpp \
    CMPL_Left.cpp \
    CMPL_Left_Provider.cpp \
    CMPL_Right.cpp \
    CMPL_Right_Provider.cpp \
    module.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1
include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/PG_InterOp -n root/cimv2 -c -s $(TARGET)

genclass:
	$(BINDIR)/genclass -r CMPL_Cross

genprov:
	$(BINDIR)/genprov CMPL_Cross
	$(BINDIR)/genprov CMPL_Left
	$(BINDIR)/genprov CMPL_Right

genmod:
	$(BINDIR)/genmod CMPL_Cross CMPL_Cross CMPL_Left CMPL_Right


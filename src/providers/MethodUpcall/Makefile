TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplemethodupcall

SOURCES = \
    CMPL_Callee.cpp \
    CMPL_Callee_Provider.cpp \
    CMPL_Caller.cpp \
    CMPL_Caller_Provider.cpp \
    module.cpp \
    repository.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genproj:
	$(BINDIR)/genproj MethodUpcall CMPL_Caller CMPL_Callee

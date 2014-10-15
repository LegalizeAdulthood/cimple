TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleunixusrprov

SOURCES = \
    module.cpp \
    repository.cpp \
    UnixUser.cpp \
    UnixUser_Provider.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r UnixUser

genprov:
	$(BINDIR)/genprov UnixUser

genmod:
	$(BINDIR)/genmod UnixUser UnixUser

regmod:
	$(BINDIR)/regmod -c $(TARGET)

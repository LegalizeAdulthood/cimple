TOP = ../../../../..
include $(TOP)/mak/config.mak

LIBRARY = junk

SOURCES = \
    Arg.cpp \
    Methods2.cpp \
    Methods.cpp \
    repository.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r Methods Methods2

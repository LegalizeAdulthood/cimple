TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass9

SOURCES = \
    main.cpp \
    Thing.cpp 

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -q -d Thing

tests:
	$(TARGET)

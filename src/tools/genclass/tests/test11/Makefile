TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test11

SOURCES = \
    main.cpp \
    repository.cpp \
    A.cpp \
    B.cpp \
    C.cpp \
    X.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r X

tests:
	$(TARGET)

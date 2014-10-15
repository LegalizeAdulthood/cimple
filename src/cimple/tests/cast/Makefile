TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_cast

SOURCES = D.cpp C.cpp B.cpp A.cpp E.cpp main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR)/genclass A B C D E

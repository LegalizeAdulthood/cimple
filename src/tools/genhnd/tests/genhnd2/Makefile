TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genhnd1

SOURCES = main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

$(BINARY): gen

gen: genclass genhnd

genclass:
	$(BINDIR)/genclass -s

genhnd:
	$(BINDIR)/genhnd -s

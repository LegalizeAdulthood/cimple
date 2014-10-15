TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass6

SOURCES = AAA2.cpp AAA.cpp BBB.cpp CCC.cpp DDD.cpp main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR)/genclass BBB CCC DDD AAA AAA2

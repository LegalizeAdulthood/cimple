TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(TOP)/schema

BINARY = genclass_test6

SOURCES = AAA2.cpp AAA.cpp BBB.cpp CCC.cpp DDD.cpp main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

genclass:
	genclass BBB CCC DDD AAA AAA2

tests:
	$(BINARY_TARGET)

TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = genclass_test6

SOURCES = AAA2.cpp AAA.cpp BBB.cpp CCC.cpp DDD.cpp main.cpp

LIBRARIES = -lcimple

include $(TOP)/mak/rules.mak

genclass:
	genclass BBB CCC DDD AAA AAA2

tests:
	$(TARGET)

TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = test_person
SOURCES = Person.cpp main.cpp
LIBRARIES = -lcimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BIN)/genclass Person

tests:

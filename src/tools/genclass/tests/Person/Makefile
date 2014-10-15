TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = test_person
SOURCES = Person.cpp main.cpp
LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BIN_DIR)/genclass Person

tests:

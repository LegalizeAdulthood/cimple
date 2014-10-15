TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = genclass_test4
SOURCES = Erp2.cpp main.cpp
LIBRARIES = -lcimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BIN)/genclass -I../mof Erp2

tests:
	$(TARGET)

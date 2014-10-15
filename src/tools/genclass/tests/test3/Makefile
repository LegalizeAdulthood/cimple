TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = genclass_test3
SOURCES = Erp.cpp main.cpp
LIBRARIES = -lcimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BIN)/genclass -I../mof Erp

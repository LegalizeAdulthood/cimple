TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = genclass_test1
SOURCES = Test1.cpp Test2.cpp main.cpp
LIBRARIES = -lcimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BIN)/genclass -I ../mof Test1 Test2

tests:
	$(TARGET)

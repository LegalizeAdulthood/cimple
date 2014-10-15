TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(TOP)/schema

BINARY = genclass_test1
SOURCES = Test1.cpp Test2.cpp main.cpp
LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BIN_DIR)/genclass -I ../mof Test1 Test2

tests:
	$(TARGET)

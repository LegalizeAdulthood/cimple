TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(TOP)/schema

BINARY = genclass_test3
SOURCES = Erp.cpp main.cpp
LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(BINARY_TARGET)

genclass:
	@ $(BIN_DIR)/genclass -I ../mof Erp

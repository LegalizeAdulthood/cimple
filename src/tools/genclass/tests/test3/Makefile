TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = genclass_test3
SOURCES = Erp.cpp main.cpp
LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(BINARY_TARGET)

genclass:
	@ $(BIN_DIR)/genclass -I ../mof Erp

TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_encoding
SOURCES = main.cpp Everything.cpp
LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN_DIR)/test_encoding

genclass:
	$(BIN_DIR)/genclass Everything

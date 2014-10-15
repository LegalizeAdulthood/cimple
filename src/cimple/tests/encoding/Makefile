TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_encoding
SOURCES = main.cpp Everything.cpp
LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:
	$(BIN_DIR)/genclass Everything

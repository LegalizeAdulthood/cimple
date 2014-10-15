TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_model_path
SOURCES = main.cpp Part.cpp Glue.cpp repository.cpp
LIBRARIES = cimple_s
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass:
	$(BIN_DIR)/genclass -r Part Glue

TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_facade
SOURCES = Base.cpp Thing.cpp Assoc.cpp main.cpp
LIBRARIES = cimpledisp cimple

include $(TOP)/mak/rules.mak

genclass:
	$(BIN_DIR)/genclass Thing Assoc Base

tests:
	@ $(BINARY_TARGET)

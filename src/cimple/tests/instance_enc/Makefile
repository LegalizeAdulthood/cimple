TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_encoding_enc
SOURCES = main.cpp Everything.cpp
LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

genclass:
	$(BIN_DIR)/genclass Everything

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)	

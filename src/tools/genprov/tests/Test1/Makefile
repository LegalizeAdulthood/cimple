TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov1
SOURCES = main.cpp Test1.cpp Test1_Provider.cpp
LIBRARIES = cimple
CLEAN += Test1.cpp Test1.h Test1_Provider.cpp Test1_Provider.h

export CIMPLE_MOF_PATH=$(TOP)/schema

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN_DIR)/test_genprov1

Test1_Provider.cpp:
	$(BIN_DIR)/genprov  -f Test1

Test1.cpp:
	$(BIN_DIR)/genclass Test1

genclass:

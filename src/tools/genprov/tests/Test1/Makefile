TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov1
SOURCES = main.cpp Test1.cpp Test1_Provider.cpp
LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN_DIR)/test_genprov1

genclass:
	genclass Test1

genprov:
	genprov  -f Test1

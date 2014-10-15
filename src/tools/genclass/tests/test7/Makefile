TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(TOP)/schema

BINARY = genclass_test7

SOURCES = main.cpp EmbeddedClass.cpp MyClass.cpp YourClass.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BIN_DIR)/genclass YourClass MyClass EmbeddedClass

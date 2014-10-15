TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(CIMPLE_MOF_PATH):../mof

BINARY = genclass_test7

SOURCES = main.cpp EmbeddedClass.cpp MyClass.cpp YourClass.cpp

LIBRARIES = -lcimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BIN)/genclass YourClass MyClass EmbeddedClass

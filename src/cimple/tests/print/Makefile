TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_print
SOURCES = main.cpp SomeClass.cpp OtherClass.cpp
LIBRARIES = cimple_s
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

genclass:
	$(BIN_DIR)/genclass SomeClass OtherClass

tests:

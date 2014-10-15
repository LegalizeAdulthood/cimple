TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = genclass_test9

SOURCES = \
    main.cpp \
    Thing.cpp 

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BIN_DIR)/genclass -q -d Thing

tests:
	@ $(BINARY_TARGET)

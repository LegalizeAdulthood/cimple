TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_class
SOURCES = main.cpp X.cpp Y.cpp Z.cpp AX.cpp AY.cpp AZ.cpp
LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	$(BINARY_TARGET)

genclass:
	$(BIN_DIR)/genclass X Y Z AX AY AZ

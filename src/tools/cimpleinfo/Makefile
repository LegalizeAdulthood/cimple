TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = cimpleinfo
SOURCES = main.cpp
LIBRARIES =
INCLUDES += -I$(SRC_DIR)/mof

ifdef CIMPLE_WINDOWS
    DEFINES += -D_CRT_SECURE_NO_DEPRECATE
endif

include $(TOP)/mak/rules.mak

tests:

genclass:

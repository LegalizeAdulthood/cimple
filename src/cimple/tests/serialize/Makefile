TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_serialize

SOURCES = \
    All_Properties.cpp \
    All_Embedded.cpp \
    main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	genclass All_Properties All_Embedded


TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_class

SOURCES = main.cpp X.cpp Y.cpp Z.cpp AX.cpp AY.cpp AZ.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	genclass X Y Z AX AY AZ

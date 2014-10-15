TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_cast
SOURCES = main.cpp X.cpp Y.cpp Z.cpp AX.cpp AY.cpp AZ.cpp
LIBRARIES = -lcimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BIN)/genclass X Y Z AX AY AZ

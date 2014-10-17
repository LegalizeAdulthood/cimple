TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_class

GENCLASS_SOURCES = X.cpp Y.cpp Z.cpp AX.cpp AY.cpp AZ.cpp

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass X Y Z AX AY AZ

TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = cimxml

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

tests:
	$(TARGET) 1.xml

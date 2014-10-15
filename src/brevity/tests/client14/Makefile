TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_client13

SOURCES = $(wildcard *.cpp)

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

CLASSES = CIM_RegisteredProfile CIM_Fan CIM_ElementConformsToProfile

gen:
	$(BINDIR)/genclass -r $(CLASSES)
	$(BINDIR)/genhnd $(CLASSES)

publish:

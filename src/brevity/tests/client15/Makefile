TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_client15

GENCLASS_SOURCES = CIM_ManagedElement.cpp repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

MOF=$(CIMPLE_ROOT)/src/providers/Employee/repository.mof

CLASSES = CIM_ManagedElement

genclass $(GENCLASS_SOURCES): $(MOF)
	$(BINDIR)/genclass -r -M $(MOF) $(CLASSES)

gen: genclass
	$(BINDIR)/genhnd -M $(MOF) $(CLASSES)

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/client15.cpp

deb:
	xgdb $(TARGET)

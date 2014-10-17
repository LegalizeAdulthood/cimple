TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_client15

GENCLASS_SOURCES = CIM_ManagedElement.cpp repository.cpp
SOURCES = $(GENCLASS_SOURCES) main.cpp

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

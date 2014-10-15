TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_client15

SOURCES = main.cpp CIM_ManagedElement.cpp repository.cpp

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

MOF=$(CIMPLE_ROOT)/src/providers/Employee/repository.mof

CLASSES = CIM_ManagedElement

gen:
	$(BINDIR)/genclass -r -M $(MOF) $(CLASSES)
	$(BINDIR)/genhnd -M $(MOF) $(CLASSES)

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/client15.cpp

deb:
	xgdb $(TARGET)

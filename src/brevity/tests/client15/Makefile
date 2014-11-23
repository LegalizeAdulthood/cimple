TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = brevity_client15

CLASSES = CIM_ManagedElement

MOF = $(TOP)/src/providers/Employee/repository.mof

GENCLASS_SOURCES = $(CLASSES:=.cpp) repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

GENHND_HEADERS = $(CLASSES:=_Hnd.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS) $(GENHND_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../libraries.mak

INCLUDES += -I../../..

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

genclass $(GENCLASS_SOURCES): $(MOF)
	$(BINDIR)/genclass -r -M $(MOF) $(CLASSES)

gen $(GENHND_HEADERS): genclass
	$(BINDIR)/genhnd -M $(MOF) $(CLASSES)

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/client15.cpp

deb:
	xgdb $(TARGET)

main.cpp: $(GENHND_HEADERS)

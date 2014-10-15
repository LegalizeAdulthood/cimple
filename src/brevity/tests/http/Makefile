TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_http

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

MOF=$(CIMPLE_ROOT)/src/providers/Employee/repository.mof

gen:
	$(BINDIR)/genclass -r -M $(MOF) $(CLASSES)
	$(BINDIR)/genhnd -M $(MOF) $(CLASSES)

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/http.cpp

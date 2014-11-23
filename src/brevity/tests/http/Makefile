TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

BINARY = brevity_http

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/http.cpp

TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = brevity_client13

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

tests:

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/client13.cpp

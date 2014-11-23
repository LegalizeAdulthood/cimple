TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = brevity_client2

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

tests:

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/client2.cpp

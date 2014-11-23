TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = brevity_client7

SOURCES = main.cpp

include ../libraries.mak

INCLUDES += -I../../.. -I../rep

include $(TOP)/mak/rules.mak

publish:
	cp main.cpp /home/mbrasher/websites/www.cimple.org/brevity/client7.cpp

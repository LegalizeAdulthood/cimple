TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = mof2html

SOURCES = main.cpp

LIBRARIES = cimplemof

INCLUDES += -I..

include $(TOP)/mak/rules.mak

run:
	mof2html -I ~/cimple/cim ~/cimple/cim/CIM_Schema.mof

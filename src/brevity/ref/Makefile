TOP = $(CIMPLE_ROOT)
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = brevity

SOURCES = \
    Client.cpp \
    Instance_Enum.cpp \
    Instance_Name_Enum.cpp \
    XML_Parser.cpp \
    CIMXML_Parser.cpp \
    CIMXML.cpp \
    Sockets.cpp \
    HTTP.cpp \

LIBRARIES = cimple

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

publish:
	cp *.h /home/mbrasher/websites/www.cimple.org/brevity

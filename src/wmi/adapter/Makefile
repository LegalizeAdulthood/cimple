TOP=../../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimplewmiadap

SOURCES = \
    SafeArr.cpp \
    utils.cpp \
    WMI_Ref.cpp \
    WMI_Adapter.cpp \
    WMI_Adapter_Factory.cpp \
    WMI_Containers.cpp \
    WMI_Thread_Context.cpp \
    WMI_Converter.cpp

LIBRARIES = cimple

#EXTRA_LINK_FLAGS = /def:link.def

EXTRA_SYS_LIBS = ole32.lib oleaut32.lib

DEFINES += -DCIMPLE_WMI_MODULE

include $(TOP)/mak/rules.mak

restart: stop start

stop:
	net stop winmgmt

start:
	net start winmgmt

inst:
	$(MAKE) stop
	$(MAKE) install
	$(MAKE) start
	- del c:\WMI_Adapter.log

TOP=../../..
include $(TOP)/mak/config.mak

LIBRARY = GadgetProvider

SOURCES = \
    Gadget.cpp \
    Gadget_Provider.cpp \
    Widget.cpp \
    Widget_Provider.cpp \
    Connector.cpp \
    Connector_Provider.cpp \
    repository.cpp \
    module.cpp \
    __ExtrinsicEvent.cpp \
    Buzzer.cpp \
    Buzzer_Provider.cpp \
    Upcall.cpp \
    Upcall_Provider.cpp

LIBRARIES = cimplewmiadap cimple

EXTRA_LINK_FLAGS = /def:link.def

EXTRA_SYS_LIBS = ole32.lib oleaut32.lib

DEFINES += -DCIMPLE_WMI_MODULE

include $(TOP)/mak/rules.mak

##==============================================================================
##
## Registration rules
##
##==============================================================================

SOURCEPATH=$(subst /,\,$(TARGET))

DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll

register:
	copy $(SOURCEPATH) $(DESTPATH)
	mofcomp -N:root/cimv2 repository.mof
	mofcomp -N:root/cimv2 register.mof
	regsvr32 /s $(DESTPATH)

unregister:
	regsvr32 /u /s $(DESTPATH)
	del /f $(DESTPATH)

restart: stop start

stop:
	net stop winmgmt

start:
	net start winmgmt

genproj:
	genproj Gadget Gadget Widget Connector Buzzer Upcall


TOP=../../..
include $(TOP)/mak/config.mak

LIBRARY = GidgetProvider

SOURCES = \
    GidgetProvider.cpp \
    GidgetProviderFactory.cpp \
    maindll.cpp

EXTRA_LINK_FLAGS = /def:GidgetProvider.def

EXTRA_SYS_LIBS = ole32.lib oleaut32.lib


include $(TOP)/mak/rules.mak

##==============================================================================
##
## Registration rules
##
##==============================================================================

SOURCEPATH=$(subst /,\,$(TARGET))

DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll

register:
	net stop winmgmt
	copy $(SOURCEPATH) $(DESTPATH)
	net start winmgmt
	mofcomp register.mof
	regsvr32 /s $(DESTPATH)

unregister:
	regsvr32 /u /s $(DESTPATH)
	del /f $(DESTPATH)

restart: stop start

stop:
	net stop winmgmt

start:
	net start winmgmt

run:
	wmic /NAMESPACE:\\root\default path gidget


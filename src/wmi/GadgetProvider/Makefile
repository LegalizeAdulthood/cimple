TOP=../../..
include $(TOP)/mak/config.mak

LIBRARY = GadgetProvider

SOURCES = \
    GadgetProvider.cpp \
    GadgetProviderFactory.cpp \
    maindll.cpp

EXTRA_LINK_FLAGS = /def:GadgetProvider.def

EXTRA_SYS_LIBS = ole32.lib oleaut32.lib


include $(TOP)/mak/rules.mak

##==============================================================================
##
## Registration rules
##
##==============================================================================

SOURCEPATH=$(subst /,\,$(TARGET))

DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll

reg:
	copy $(SOURCEPATH) $(DESTPATH)
	mofcomp register.mof
	regsvr32 /s $(DESTPATH)

unreg:
	regsvr32 /u /s $(DESTPATH)
	del /f $(DESTPATH)

restart: stop start

stop:
	net stop winmgmt

start:
	net start winmgmt

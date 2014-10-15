TOP=../../..
include $(TOP)/mak/config.mak

LIBRARY = Person

SOURCES = \
    Person.cpp \
    Person_Provider.cpp \
    module.cpp \
    repository.cpp

LIBRARIES = cimplewmiadap cimple

EXTRA_LINK_FLAGS = /def:link.def

EXTRA_SYS_LIBS = ole32.lib oleaut32.lib

DEFINES += -DCIMPLE_WMI_MODULE

include $(TOP)/mak/rules.mak

reg:
SOURCEPATH=$(subst /,\,$(TARGET))

DESTPATH=c:\WINDOWS\system32\wbem\$(LIBRARY).dll

reg:
	copy $(SOURCEPATH) c:\WINDOWS\system32\wbem
	mofcomp repository.mof
	mofcomp register.mof
	regsvr32 /s $(DESTPATH)

unreg:
	regsvr32 /u /s $(DESTPATH)

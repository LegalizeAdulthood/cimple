TOP = ../../..

include $(TOP)/mak/config.mak

SHARED_LIBRARY=cimplewidget

SOURCES = \
    CIMPLE_Widget.cpp \
    repository.cpp \
    CIMPLE_Widget_Provider.cpp \
    module.cpp

DEFINES += -DCIMPLE_CMPI_MODULE

LIBRARIES += cimplecmpiadap cimple

include $(TOP)/mak/rules.mak

##==============================================================================
##
## The following rule registers this provider with the SFCB.
##
##==============================================================================

SFCB_MOFSDIR=/usr/var/lib/sfcb/stage/mofs
SFCB_REGSDIR=/usr/var/lib/sfcb/stage/regs

register:
	cp $(TARGET) /usr/lib64/
	cp CIMPLE_Widget.mof $(SFCB_MOFSDIR)/CIMPLE_Widget.mof
	cp CIMPLE_Widget.reg $(SFCB_REGSDIR)/CIMPLE_Widget.reg
	sfcbrepos


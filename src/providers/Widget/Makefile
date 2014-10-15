## This provider is defined only for use in testing sfcb and CIMPLE today

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

## Not utilized with sfcb today.  Registration
## with sfcb is defined as target below
##regmod:
##	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r CIMPLE_Widget

genprov:
	$(BINDIR)/genprov CIMPLE_Widget

genmod:
	$(BINDIR)/genmod CIMPLE_Widget CIMPLE_Widget

##==============================================================================
##
## The following rule registers this provider with the SFCB.
## Registration for SFCB is manual and not part of the overal make structure
##
##==============================================================================

## This may change per users needs
SFCB_MOFSDIR=/usr/local/var/lib/sfcb/stage/mofs/root/cimv2
SFCB_REGSDIR=/usr/local/var/lib/sfcb/stage/regs
SFCB_NAMESPACE=root/cimv2

## Note that we are forcing copy of target to lib64 for now.
## Currently there is an issue with use of other directories for sfcb
## at least in some Linux platforms.
register-sfcb:
	cp $(TARGET) /usr/lib64/
	cp CIMPLE_Widget.mof $(SFCB_MOFSDIR)/CIMPLE_Widget.mof
	cp CIMPLE_Widget.reg $(SFCB_REGSDIR)/CIMPLE_Widget.reg
	sfcbrepos

## simple tests of the Widget class and instances.	
## live manual tests using Pegasus cimcli	
live-manual:
	cimcli ns -l localhost
	cimcli gc CIMPLE_Widget -l localhost -n $(SFCB_NAMESPACE)
	cimcli ni CIMPLE_Widget -l localhost -n $(SFCB_NAMESPACE)
	cimcli ei CIMPLE_Widget -l localhost -n $(SFCB_NAMESPACE)
	


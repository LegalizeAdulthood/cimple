TOP=.
include $(TOP)/mak/config.mak

DIRS = src schema

include $(TOP)/mak/rules.mak

##==============================================================================
##
## distclean:
##
##==============================================================================

check:
	$(MAKE) tests

distclean: clean
	$(call rm,config.options)
	$(call rm,src/cimple/options.h)
	$(call rmdirhier,$(LIBDIR))
	$(call rmdirhier,$(BINDIR))

##==============================================================================
##
## regress:
##
##==============================================================================

CIMSERVER = $(WITH_PEGASUS_OPT)/bin/cimserver

ifeq ($(PEGASUS_PLATFORM),WIN32_IX86_MSVC)
  SLEEP = ./bin/csleep
else
  SLEEP = sleep
endif

stop_cimserver:
ifeq ($(PEGASUS_PLATFORM),WIN32_IX86_MSVC)
	- $(CIMSERVER) -stop
else
	- $(CIMSERVER) -s
endif
	$(SLEEP) 3

start_cimserver:
ifeq ($(PEGASUS_PLATFORM),WIN32_IX86_MSVC)
	- $(CIMSERVER) -start
else
	- $(CIMSERVER)
endif
	$(SLEEP) 3

prepare:
	$(MAKE) install
	$(MAKE) insmod
	$(MAKE) -C $(PEGASUS_ROOT) repository

run:
	$(MAKE) tests
	$(MAKE) regmod
	$(MAKE) live

regress:
	$(MAKE) stop_cimserver
	$(MAKE) prepare
	$(MAKE) start_cimserver
	$(MAKE) run
	$(MAKE) stop_cimserver
	$(ECHONL)
	$(ECHO) "==== Regression suite passed"

world: clean all regress

##==============================================================================
##
## tag:
##
##==============================================================================

MAJOR=1
MINOR=1
REVISION=0
VERSION=$(MAJOR).$(MINOR).$(REVISION)
TAG=cimple_$(MAJOR)_$(MINOR)_$(REVISION)

tag:
	@ cvs tag -F $(TAG) > /dev/null
	@ echo "Added $(TAG) tag"

##==============================================================================
##
## dist:
##
##==============================================================================

DISTROOT=cimple-$(VERSION)
TARDIST=$(DISTROOT).tar.gz
ZIPDIST=$(DISTROOT).zip

dist:
	@ rm -f /tmp/$(TARDIST)
	@ rm -f /tmp/$(ZIPDIST)
	@ rm -rf /tmp/$(DISTROOT)
	@ cp -r . /tmp/$(DISTROOT)
	@ ( cd /tmp/$(DISTROOT); $(MAKE) distclean > /dev/null )
	@ rm -rf `find /tmp/$(DISTROOT) -name CVS`
	@ echo "Creating /tmp/$(TARDIST)..."
	@ ( cd /tmp ; tar zcf $(TARDIST) $(DISTROOT) )
	@ echo "Creating /tmp/$(ZIPDIST)..."
	@ ( cd /tmp/$(DISTROOT) ; zip -q -R ../$(ZIPDIST) '*' )
	@ rm -rf /tmp/$(DISTROOT)

##==============================================================================
##
## publish:
##
##==============================================================================

publish:
	cp /tmp/$(TARDIST) $(HOME)/websites/www.cimple.org
	cp /tmp/$(ZIPDIST) $(HOME)/websites/www.cimple.org
	rm -rf /tmp/$(TARDIST)
	rm -rf /tmp/$(ZIPDIST)



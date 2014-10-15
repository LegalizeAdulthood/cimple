
CIMPLE_PLATFORM=

-include mak/platform.mak

ifeq ($(CIMPLE_PLATFORM),)
  $(error "First type ./configure")
endif

all: mut
	$(MAKE) -C src

depend: mut
	$(MAKE) -C src depend

clean: mut
	$(MAKE) -C src clean

tests: mut
	$(MAKE) -C src tests

gen: mut
	$(MAKE) -C src gen

sub: mut
	$(MAKE) -C src sub

genclass: mut
	$(MAKE) -C src genclass

chksrc: mut
	$(MAKE) -C src chksrc

reg: mut
	$(MAKE) -C src/providers reg

live-tests: mut
	$(MAKE) -C src/providers live-tests
	$(MAKE) -C src/pegasus/clients/LampIndicClientListener live-tests

mut:
ifeq ($(CIMPLE_PLATFORM),WIN32_IX86_MSVC)
	$(MAKE) -C src/tools/mut
endif

distclean: clean
	$(RM) mak/platform.mak
	$(RM) src/platform.h
	$(RM) cimpleinfo.out

##==============================================================================
##
## regress:
##
##==============================================================================

__stop_cimserver:
ifeq ($(PEGASUS_PLATFORM),WIN32_IX86_MSVC)
	- cimserver -stop
else
	- cimserver -s
endif
	csleep 3

__start_cimserver:
ifeq ($(PEGASUS_PLATFORM),WIN32_IX86_MSVC)
	- cimserver -start
else
	- cimserver
endif
	csleep 3

regress:
	$(MAKE) tests
	$(MAKE) __stop_cimserver
	$(MAKE) -C $(PEGASUS_ROOT) repository
	$(MAKE) reg
	$(MAKE) __start_cimserver
	$(MAKE) live-tests
	$(MAKE) __stop_cimserver

setup:
	$(MAKE) -C $(PEGASUS_ROOT) repository
	$(MAKE) reg

##==============================================================================
##
## release:
##
##==============================================================================

MAJOR=0
MINOR=99
REVSION=56
VERSION=$(MAJOR).$(MINOR).$(REVSION)
DISTROOT=cimple-$(VERSION)
TARDIST=$(DISTROOT).tar.gz
ZIPDIST=$(DISTROOT).zip
TAG=cimple_$(MAJOR)_$(MINOR)_$(REVSION)

tag:
	@ cvs tag -F $(TAG) > /dev/null
	@ echo "Added $(TAG) tag"

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

publish:
	cp /tmp/$(TARDIST) $(HOME)/websites/www.cimple.org
	cp /tmp/$(ZIPDIST) $(HOME)/websites/www.cimple.org
	rm -rf /tmp/$(TARDIST)
	rm -rf /tmp/$(ZIPDIST)

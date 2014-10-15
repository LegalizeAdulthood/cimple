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

##==============================================================================
##
## release:
##
##==============================================================================

VERSION=0.99.20-beta
PREFIX=$(HOME)/inova/www.cimple.org
PACKAGE=$(PREFIX)/cimple-$(VERSION).tar.gz

release:
	$(MAKE) distclean > /dev/null
	@ ( cd ..; tar zcf $(PACKAGE) cimple )
	@ cp doc/release-notes-$(VERSION).txt $(PREFIX)
	@ echo "Created $(PACKAGE)..."

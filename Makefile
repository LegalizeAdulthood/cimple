##==============================================================================
##
## Top Level Makefile for CIMPLE.  This Makefile includes functionality both
## for the CIMPLE user (make, make install, make check) and for the CIMPLE
## Developers (detailed tests, tagging, distribution cration, etc.)
##
##==============================================================================
TOP=.

include $(TOP)/mak/config.mak

DIRS = src mak

ifneq ($(PLATFORM),VXWORKS_XSCALE_GNU)
  DIRS += schema
endif

## include other mak files based on the current activity
## Activities are defined by keywords in other Makefiles (ex. DIRS,
## SHARED_LIBRARY, BINARY, etc. These are further refined by other
## keyword in particular included Makefiles such as INSTALL, INSMOD)

include $(TOP)/mak/rules.mak

##==============================================================================
##
## check - runs the unit test target (tests:) on directory hiearchy
##         check does not run live tests.
##
##==============================================================================

check:
	$(MAKE) tests

##==============================================================================
##
## regress: Executes regression tests against Pegasus.
##          Requires PEGASUS_ROOT defined.
##          The install registers test and sample providers that
##          include regmod target with Pegasus
##
##==============================================================================

CIMSERVER = $(WITH_PEGASUS_OPT)/bin/cimserver

##
##  Server start and stop operations. All platforms except
##  windows uses same command format.
##
stop_cimserver:
ifeq ($(findstring _MSVC, $(PEGASUS_PLATFORM)), _MSVC)
	- $(CIMSERVER) -stop
else
	- $(CIMSERVER) -s
endif
	$(SLEEP) 3

start_cimserver:
ifeq ($(findstring _MSVC, $(PEGASUS_PLATFORM)), _MSVC)
	- $(CIMSERVER) -start
else
	- $(CIMSERVER)
endif
	$(SLEEP) 3

## Execute the install of cimple libraries,providers (insmod),
## and  a repository make on pegasus to clean the repository.
## We do not use the Pegasus test repository (make testrepository)
prepare:
	$(MAKE) install
	$(MAKE) insmod
	$(MAKE) -C $(PEGASUS_ROOT) repository

# run unit tests (all Makefiles with tests target),
#     register providers that have regmod target in Makefile,
#     run all programs defined with live target in Makefile
#     Server must be running for this step.
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

##==============================================================================
##
## world:  Run build tests register live tests, regression tests against pegasus
##         make world is good test of changes and primarily
##         for cimple developers.  Requires Pegasus setup and runable
##         Requires PEGASUS_ROOT defined.
##            
##
##==============================================================================

world: clean all regress

##==============================================================================
##
## cmpiworld:  Run build, tests, register, live, tests, regression tests against
##         with an environment variable set to create CMPI providers for
##         those test providers that can be rebuilt for both C++ and cmpi
##         This is primarily a test target for the developers of CIMPLE
##            
##
##==============================================================================

cmpiworld:
	CIMPLE_PROVIDER_BUILD_CMPI=1
	$(MAKE) world

##==============================================================================
## Start the pegasus server with valgrind.  Note that this is a Linux tool
## it also starts the server in the calling terminal window.
## Useful for server and provider memory allocation tests
##==============================================================================

server_vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(CIMSERVER) daemon=false 

##==============================================================================
##
## tag: Tag CVS with the release tag defined below.
##
##==============================================================================

# The Version components MUST BE Numerics
# NOTE: Developers. src/cimple/config.h version definition MUST match this
# definition or execution of providers will fail
MAJOR=2
MINOR=0
REVISION=18
VERSION=$(MAJOR).$(MINOR).$(REVISION)
TAG=cimple_$(MAJOR)_$(MINOR)_$(REVISION)

tag:
	@ cvs tag -F $(TAG) > /dev/null
	@ echo "Added $(TAG) tag"

##==============================================================================
##
## stabletag: Move the STABLE tag forward
##
##==============================================================================

stabletag:
	@ cvs tag -F STABLE > /dev/null
	@ echo "Moved STABLE tag"

##==============================================================================
##
## distclean: Clean the source tree for a distribution
##            Invoked by the dist target. 
##            Cleans out number of things that are not part of distribution
##
##==============================================================================

distclean: clean
	$(call rm,config.options)
	$(call rm,src/cimple/options.h)
	$(call rmdirhier,./lib)
	$(call rmdirhier,./lib64)
	$(call rmdirhier,$(BINDIR))
	$(call rmdirhier,*~)
	$(call rmdirhier,src/wmi/Sample)
	
##==============================================================================
##
## dist: create tar and zip distribution in a tmp directory
## Developer functions. Designed for us with *nix OS
## 
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
## publish: Publish the distributions on the cimple.org site
##   Developer function. Designed to be used with *nix OS
##
##==============================================================================

publish:
	cp /tmp/$(TARDIST) $(WEBSITE)
	cp /tmp/$(ZIPDIST) $(WEBSITE)
	rm -rf /tmp/$(TARDIST)
	rm -rf /tmp/$(ZIPDIST)

##==============================================================================
##
## clean-all
## Developer function. Designed for *nix OS types. Cleans out
## all objects and the libraries associated with building
##
##==============================================================================

clean-all:
	rm -rf ./lib
	rm -rf ./lib64
	rm -rf ./bin
	rm -f `find . -name '*.o'`


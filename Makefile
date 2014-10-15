
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

mut:
ifeq ($(CIMPLE_PLATFORM),WIN32_IX86_MSVC)
	$(MAKE) -C src/tools/mut
endif

distclean: clean
	$(RM) mak/platform.mak
	$(RM) src/platform.h

regress:
	( cimserver -s; sleep 1 )
	( cd $(PEGASUS_ROOT); make repository )
	$(MAKE) reg
	( cimserver; sleep 3 )
	$(MAKE) live-tests
	cimserver -s

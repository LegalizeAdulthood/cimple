TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_log

SOURCES = main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

## set local definition of CIMPLE_HOME env var for this test to
## the current directory. This env variable is used in the
## test program with the api set_cimple_home_envvar to test that
## function.
export CIMPLE_HOME_TEST=$(CURDIR)

## set as runtests because we do not have common DIFF and CUT
## for all platforms
## This test tests for exact log output information.
tests:
##  remove any temporary files
	@ $(RM) -rf .cimple 
	@ $(RM) -rf .cimplerc

	echo CIMPLE_HOME_TEST = $(CIMPLE_HOME_TEST)

##  execute the program
	@ $(BINDIR)/$(BINARY)

## test output in .cimple for messages
## TODO this test is worthless since all options testing should
## be within main.cpp.

ifdef DISABLE_LOG_MACROS_OPT
	$(ECHO) should be no log
endif
	@ $(RM) .cimple -rf
	@ $(RM) .cimplerc -rf
##
vg:
	echo CIMPLE_HOME_TEST = $(CIMPLE_HOME_TEST)
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
	@ $(RM) .cimple -rf
	@ $(RM) .cimplerc

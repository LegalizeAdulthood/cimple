TOP = .
include $(TOP)/mak/config.mak

DIRS = src

include $(TOP)/mak/dir.mak

##
## Register the test providers with Pegasus.
##
reg:
	( $(MAKE) -C $(TOP)/src/providers reg )

##
## Run live tests against Pegasus server:
##
live-tests:
	( $(MAKE) -C $(TOP)/src/providers live-tests )

##==============================================================================
##
## cmpi.mak
##
##     This makefile specifies the location of these CMPI header files:
##
##         <cmpidt.h>
##         <cmpift.h>
##         <cmpimacs.h>
##
##     You may override CMPI_ROOT in your environment, to use an alternative
##     CMPI implementation when building CMPI.
##
##==============================================================================

ifndef CMPI_ROOT
  CMPI_ROOT = $(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI
endif

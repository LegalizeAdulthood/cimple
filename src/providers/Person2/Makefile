TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplperson2

INCLUDES += -I../repository

SOURCES = Person2_Provider.cpp Link2_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -c $(TARGET)

genclass:

##==============================================================================
##
## Test rules
##
##==============================================================================

tests:

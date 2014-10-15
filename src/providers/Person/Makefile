TOP = ../../..
include $(TOP)/mak/config.mak

ifdef PEGASUS_HOME
include $(TOP)/mak/pegasus.mak
endif

SH_LIBRARY = cmplperson

INCLUDES += -I../repository

SOURCES = Person_Provider.cpp Link_Provider.cpp module.cpp

LIBRARIES = -lcimple -lcmplrep

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

ei:
	CLI ei Person

ni:
	CLI ni Person

gi:
	CLI gi Person.ssn=2

di:
	CLI di Person.ssn=2

ci:
	create_person

mi:
	modify_person

cs:
	( cimserver -s ; sleep 1; cimserver )

cat:	
	catmod $(TARGET)

tests:
	@ $(BIN)/dlopen $(TARGET)

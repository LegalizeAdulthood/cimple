TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplperson

INCLUDES += -I../repository

SOURCES = Person_Provider.cpp Link_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

LIBRARIES += cimplepegadap

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

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
	catmod $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

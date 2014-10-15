TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplperson2

INCLUDES += -I../repository

SOURCES = Person2_Provider.cpp Link2_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

genclass:

##==============================================================================
##
## Test rules
##
##==============================================================================

tests:

ei:
	$(CIMCLI) ei Person2

ni:
	$(CIMCLI) ni Person2

gi:
	$(CIMCLI) gi Person2.ssn=2

di:
	$(CIMCLI) di Person2.ssn=2

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

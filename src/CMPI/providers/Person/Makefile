TOP = ../../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = PersonProvider

INCLUDES += -I$(TOP)/src/providers/repository 
INCLUDES += -I$(TOP)/src/CMPI/cmpi
INCLUDES += $(CMPI_INCLUDES)

SOURCES = Person_Provider.cpp Link_Provider.cpp module.cpp

LIBRARIES = cimple cmplrep cimplecmpi

INCLUDES += -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -m -c $(TARGET)

reg2:
	cimmofl -w $(TOP)/src/providers/repository/Person.mof
	cimmofl -w -n root/PG_InterOp Registration.mof


genclass:
	genclass Person
	genclass Link

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

TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplperson

SOURCES = \
    repository.cpp \
    Person.cpp \
    Salesman.cpp \
    PersonLink.cpp \
    SalesmanLink.cpp \
    Person_Provider.cpp \
    PersonLink_Provider.cpp \
    Salesman_Provider.cpp \
    SalesmanLink_Provider.cpp \
    module.cpp

LIBRARIES = cimple

#BUILD_CMPI_PROVIDER=1

ifdef BUILD_CMPI_PROVIDER
  LIBRARIES += cimplecmpiadap
  DEFINES += -DBUILD_CMPI_PROVIDER
else
  LIBRARIES += cimplepegadap
endif

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
	$(CIMCLI) ei Person

ni:
	$(CIMCLI) ni Person

gi:
	$(CIMCLI) gi Person.ssn=2

di:
	$(CIMCLI) di Person.ssn=2

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

genclass:
	genclass -r Person PersonLink Salesman SalesmanLink

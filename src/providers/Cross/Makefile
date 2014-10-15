TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = Lamp

SOURCES = \
    CMPL_Cross.cpp \
    CMPL_Cross_Provider.cpp \
    CMPL_Left.cpp \
    CMPL_Left_Provider.cpp \
    CMPL_Right.cpp \
    CMPL_Right_Provider.cpp \
    module.cpp \
    repository.cpp

LIBRARIES = cimple

ifdef BUILD_CMPI_PROVIDER
  LIBRARIES += cimplecmpiadap
  DEFINES += -DBUILD_CMPI_PROVIDER
else
  LIBRARIES += cimplepegadap
endif

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

reg:
	regmod -n root/PG_InterOp -n root/cimv2 -c -s $(SHARED_LIBRARY_TARGET)

genclass:
	genclass -r CMPL_Cross

tests:

TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplmyindic

INCLUDES += -I../repository

SOURCES = \
    MyIndication_Provider.cpp \
    module.cpp

LIBRARIES = cimple cmplrep

include $(TOP)/mak/rules.mak

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

ifdef CIMPLE_WINDOWS
    DEV_NULL=.dev.null
else
    DEV_NULL=/dev/null
endif

reg:
	regmod -c $(TARGET)

xxx:
	cimmofl ../repository/MyEmbeddedClass.mof 2> $(DEV_NULL)

genclass:

tests:
	@ $(BIN)/dlopen $(TARGET)

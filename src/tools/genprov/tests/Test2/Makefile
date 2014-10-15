TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov2

SOURCES = \
    main.cpp \
    Test2.cpp \
    Test2_Provider.cpp \
    Test2Link.cpp \
    Test2Link_Provider.cpp

LIBRARIES = cimple

CLEAN += \
    Test2.h \
    Test2.cpp \
    Test2_Provider.h \
    Test2_Provider.cpp \
    Test2Link.h \
    Test2Link.cpp \
    Test2Link_Provider.h \
    Test2Link_Provider.cpp \

export CIMPLE_MOF_PATH=$(TOP)/schema

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN)/test_genprov2

Test2_Provider.cpp:
	genprov  -f Test2

Test2.cpp:
	genclass Test2

Test2Link_Provider.cpp:
	genprov  -f Test2Link

Test2Link.cpp:
	genclass Test2Link

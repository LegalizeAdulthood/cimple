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

include $(TOP)/mak/rules.mak

tests:
	@ $(BIN_DIR)/test_genprov2

genclass:
	genclass Test2
	genclass Test2Link

genprov:
	genprov  -f Test2
	genprov  -f Test2Link

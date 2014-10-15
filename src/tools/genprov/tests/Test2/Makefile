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
	@ $(BINDIR)/test_genprov2

genclass:
	$(BINDIR)/genclass Test2
	$(BINDIR)/genclass Test2Link

genprov:
	$(BINDIR)/genprov  -f Test2
	$(BINDIR)/genprov  -f Test2Link

genmod:
	$(BINDIR)/genmod Test2 Test2 Test2Link

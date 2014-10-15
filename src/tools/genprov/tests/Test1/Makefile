TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genprov1
SOURCES = main.cpp Test1.cpp Test1_Provider.cpp
LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(BINDIR)/test_genprov1

genclass:
	$(BINDIR)/genclass Test1

genprov:
	$(BINDIR)/genprov Test1

genmod:
	$(BINDIR)/genmod Test1 Test1

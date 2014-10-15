TOP=../../../..
include $(TOP)/mak/config.mak

all:
depend:
gen:

tests:
	$(BINDIR)/mofc -I $(TOP)/schema/cim2131 tests.mof
	@ $(ECHO) "+++++ passed all tests ($(BINDIR)/mofc)"

CLEAN += memstream.tmp

clean:
	$(call rm,$(CLEAN))

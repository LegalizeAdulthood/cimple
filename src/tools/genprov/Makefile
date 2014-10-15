TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = genprov

SOURCES = main.cpp

LIBRARIES = cimplemof cimplegencommon cimpleutil cimple

INCLUDES += -I$(SRC_DIR)/mof

include $(TOP)/mak/rules.mak

tests:

file2c = $(BINDIR)/file2c -n $(1) $(1).h.in > $(1).h

gen:
	$(call file2c, header_prefix)
	$(call file2c, header_suffix)
	$(call file2c, source_prefix)
	$(call file2c, source_suffix)
	$(call file2c, indication_header_prefix)
	$(call file2c, indication_header_suffix)
	$(call file2c, indication_source_prefix)
	$(call file2c, association_header)
	$(call file2c, association_source)
	$(call file2c, module_source)

usage:
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

TOP = ../../..
include $(TOP)/mak/config.mak

BINARY = genprov
SOURCES = main.cpp
LIBRARIES = -lmof -lcimplegencommon -lcimpleutil
INCLUDES += -I$(SRC)/mof

include $(TOP)/mak/rules.mak

tests:

file2c = file2c -n $(1) $(1).h.in > $(1).h

gen:
	$(call file2c, header_prefix)
	$(call file2c, header_suffix)
	$(call file2c, source_prefix)
	$(call file2c, source_infix1)
	$(call file2c, source_infix2)
	$(call file2c, source_suffix)
	$(call file2c, indication_header_prefix)
	$(call file2c, indication_header_suffix)
	$(call file2c, indication_source_prefix)
	$(call file2c, indication_source_infix1)
	$(call file2c, indication_source_infix2)
	$(call file2c, module_source)

usage:
	file2c usage.txt -n USAGE > usage.h

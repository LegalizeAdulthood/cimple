TOP = ../../../..
include $(TOP)/mak/config.mak

SCHEMA = cim214
SCHEMA_FILE = CIM_Schema.mof
SCHEMA_DIR=$(TOP)/schema/$(SCHEMA)


all:
	$(BINDIR)/mof2html -v $(SCHEMA) -I $(SCHEMA_DIR) \
	 	$(SCHEMA_DIR)/$(SCHEMA_FILE)

clean:
	$(RM) *.html

test:
	firefox index.html



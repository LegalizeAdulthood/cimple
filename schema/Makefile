TOP = ..
include $(TOP)/mak/config.mak

all:

define NL


endef

SDIRS = cim2131 cim214

SCHEMA_DIR=$(DATADIR_OPT)/cimple/schema

install: uninstall
	$(call mkdirhier,$(DESTDIR)$(SCHEMA_DIR))
	$(foreach i, $(SDIRS), \
            $(call cpdirhier,$i,$(DESTDIR)$(SCHEMA_DIR)/$i) $(NL))

uninstall:
	$(call rmdirhier,$(DESTDIR)$(SCHEMA_DIR))

include $(TOP)/mak/rules.mak

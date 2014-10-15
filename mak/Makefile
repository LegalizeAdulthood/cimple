TOP = ..
include $(TOP)/mak/config.mak

all:

CIMPLEDIR=$(DATADIR_OPT)/cimple
MAKDIR=$(CIMPLEDIR)/mak

install: uninstall
	$(call mkdirhier,$(DESTDIR)$(CIMPLEDIR))
	$(call cpdirhier,$(TOP)/mak,$(DESTDIR)$(MAKDIR))
	$(call cp,$(TOP)/config.options,$(DESTDIR)$(CIMPLEDIR))

uninstall:
	$(call rmdirhier,$(DESTDIR)$(MAKDIR))
	$(call rm,$(DESTDIR)$(CIMPLEDIR)/config.options)

install:

clean:

include $(TOP)/mak/rules.mak

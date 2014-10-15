ifneq ($(PLATFORM),VXWORKS_XSCALE_GNU)
  ifeq ($(WITH_PEGASUS_OPT),)
    $(error \
    "CIMPLE not configured for Pegasus: try ./configure --pegasus-prefix=DIR")
  endif
endif

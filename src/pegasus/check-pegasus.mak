ifeq ($(WITH_PEGASUS_OPT),)
$(error \
    "CIMPLE not configured for Pegasus: try ./configure --pegasus-prefix=DIR")
endif

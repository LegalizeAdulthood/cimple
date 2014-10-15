TOP = ../../..
include $(TOP)/mak/config.mak

DIRS = \
    array \
    atomicint \
    buffer \
    cast \
    class \
    classes \
    clone \
    Cond \
    cond_queue \
    cond_queue2 \
    datetime \
    find_token \
    join \
    log \
    mutex \
    model_path \
    print \
    property \
    string \
    sizes \
    time \
    type \
    value

## Temporary bypass for windows becasue of issue
## in test
## TODO - Fix This issue
ifdef CIMPLE_UNIX
    DIRS += io
endif 

ifdef ENABLE_SCHEDULER_OPT
    DIRS += lists scheduler
endif



include $(TOP)/mak/rules.mak

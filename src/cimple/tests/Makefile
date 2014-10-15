TOP = ../../..
include $(TOP)/mak/config.mak

DIRS = \
    array \
    atomicint \
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
    mutex \
    model_path \
    print \
    property \
    string \
    sizes \
    time \
    type \
    value

ifdef ENABLE_SCHEDULER_OPT
    DIRS += lists scheduler
endif



include $(TOP)/mak/rules.mak

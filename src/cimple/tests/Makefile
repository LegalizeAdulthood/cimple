TOP = ../../..
include $(TOP)/mak/config.mak

DIRS = \
    array \
    cast \
    class \
    clone \
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

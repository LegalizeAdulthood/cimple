TOP = ../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimple

SOURCES = \
    Atomic.cpp \
    Cond_Queue.cpp \
    Exception.cpp \
    boolean.cpp \
    real.cpp \
    Arg.cpp \
    Ops.cpp \
    Instance_Hnd.cpp \
    Instance_Ref.cpp \
    log.cpp \
    File_Lock.cpp \
    integer.cpp \
    Value.cpp \
    Container.cpp \
    Buffer.cpp \
    octets.cpp \
    config.cpp \
    ptr_array.cpp \
    io.cpp \
    flags.cpp \
    Meta_Value.cpp \
    Meta_Repository.cpp \
    Meta_Qualifier.cpp \
    Meta_Reference.cpp \
    Thread_Context.cpp \
    cimom.cpp \
    Cond.cpp \
    Error.cpp \
    Mutex.cpp \
    Time.cpp \
    Thread.cpp \
    Auto_Mutex.cpp \
    Provider_Handle.cpp \
    Array_Impl.cpp \
    cimple.cpp \
    Datetime.cpp \
    Instance.cpp \
    Instance_Map.cpp \
    Meta_Feature.cpp \
    Meta_Class.cpp \
    Meta_Method.cpp \
    Meta_Property.cpp \
    Registration.cpp \
    String.cpp \
    Strings.cpp \
    Type.cpp \
    Property.cpp \
    TSD.cpp

## The scheduler is an optional component so is
## compiled only if flag set
ifdef ENABLE_SCHEDULER_OPT
    SOURCES += List.cpp Id_Pool.cpp Scheduler.cpp
endif

## obsolete, see top/doc/SDK
CIMPLE_DOXYGEN_FILES = \
    Instance.h \
    Ref.h \
    String.h \
    Array.h \
    DateTime.h \
    Thread.h \
    Cond.h \
    Cond_Queue.h \
    Mutex.h \
    AutoMutex.h \
    TSD.h \
    cimom.h \
    Stack.h \
    log.h \
    Arg.h \
    Time.h \
    Thread.h \
    Stack.h \
    octets.h \
    AtomicCounter.h

## Obsolete 
 ifdef ENABLE_SCHEDULER_OPT
    CIMPLE_DOXYGEN_FILES += List.h Id_Pool.h Scheduler.h
endif
   
DEFINES += -DCIMPLE_BUILDING_LIBCIMPLE

INSTALL_HEADERS_DIR = cimple

INSTALL_HEADERS = $(wildcard *.h)

include $(TOP)/mak/rules.mak

doc: docclean
        
	doxygen

docclean:
	rm doxygenout -rf

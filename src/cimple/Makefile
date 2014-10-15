TOP = ../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimple

SOURCES = \
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
    Exception.cpp \
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

DEFINES += -DCIMPLE_BUILDING_LIBCIMPLE

INSTALL_HEADERS_DIR = cimple

INSTALL_HEADERS = $(wildcard *.h)

include $(TOP)/mak/rules.mak

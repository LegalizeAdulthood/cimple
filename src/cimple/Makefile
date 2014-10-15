TOP = ../..
include $(TOP)/mak/config.mak

INSTALL=1

LIBRARY = cimple

SOURCES = \
    config.cpp \
    Tracer.cpp \
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
    Hnd.cpp \
    TSD.cpp

DEFINES += -DCIMPLE_BUILDING_LIBCIMPLE

INSTALL_HEADERS_DIR = cimple

INSTALL_HEADERS = \
    Array.h \
    Array_Impl.h \
    Atomic_Counter.h \
    Atomic_DARWIN_IX86_GNU.h \
    Atomic_DARWIN_PPC_GNU.h \
    Atomic.h \
    Atomic_LINUX_IA64_GNU.h \
    Atomic_LINUX_IX86_GNU.h \
    Atomic_LINUX_PPC_GNU.h \
    Atomic_LINUX_S390_GNU.h \
    Atomic_WIN32_IX86_MSVC.h \
    Auto_Mutex.h \
    char16.h \
    cimom.h \
    cimple.h \
    Cond.h \
    config.h \
    options.h \
    Datetime.h \
    Error.h \
    flags.h \
    flavor.h \
    Hnd.h \
    Instance.h \
    Instance_Map.h \
    io.h \
    linkage.h \
    Magic.h \
    Meta_Class.h \
    Meta_Feature.h \
    Meta_Method.h \
    Meta_Property.h \
    Meta_Qualifier.h \
    Meta_Reference.h \
    Meta_Repository.h \
    Meta_Value.h \
    Mutex.h \
    platform_DARWIN.h \
    platform_DARWIN_IX86_GNU.h \
    platform_DARWIN_PPC_GNU.h \
    platform_LINUX.h \
    platform_LINUX_IA64_GNU.h \
    platform_LINUX_IX86_GNU.h \
    platform_LINUX_PPC_GNU.h \
    platform_LINUX_S390_GNU.h \
    platform_LINUX_X86_64_GNU.h \
    platform_WIN32_IX86_MSVC.h \
    Property.h \
    Provider.h \
    Provider_Handle.h \
    ptr_array.h \
    Ref.h \
    Registration.h \
    scope.h \
    String.h \
    Strings.h \
    Thread_Context.h \
    Thread.h \
    Time.h \
    Tracer.h \
    TSD.h \
    Type.h

include $(TOP)/mak/rules.mak

zzz:
	echo $(STATIC_CXX)

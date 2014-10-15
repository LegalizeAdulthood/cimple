TOP = ../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cimple
STATIC_LIBRARY = cimple_s

SOURCES = \
    Thread_Context.cpp \
    Ref.cpp \
    cimom.cpp \
    Atomic_Counter.cpp \
    Cond.cpp \
    Error.cpp \
    version.cpp \
    Mutex.cpp \
    Time.cpp \
    Thread.cpp \
    Auto_Mutex.cpp \
    Provider_Handle.cpp \
    Array.cpp \
    Array_Impl.cpp \
    Atomic.cpp \
    cimple.cpp \
    config.cpp \
    Datetime.cpp \
    Instance.cpp \
    Instance_Map.cpp \
    Meta_Class.cpp \
    Meta_Feature.cpp \
    Meta_Method.cpp \
    Meta_Property.cpp \
    Meta_Reference.cpp \
    Provider.cpp \
    Registration.cpp \
    String.cpp \
    Strings.cpp \
    Type.cpp \
    Property.cpp

LIBRARIES =

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLE_BUILDING_LIBCIMPLE

include $(TOP)/mak/rules.mak

genclass:

doc:
	rm -rf doxygen
	doxygen Doxyfile

create-Doxyfile:
	doxygen -g

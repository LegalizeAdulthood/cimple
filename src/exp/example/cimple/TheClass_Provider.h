#ifndef _TheClass_Provider_h
#define _TheClass_Provider_h

#include <cimple/cimple.h>
#include "TheClass.h"

CIMPLE_NAMESPACE_BEGIN

class TheClass_Provider
{
public:

    typedef TheClass Class;

    TheClass_Provider();

    CIMPLE_HIDE ~TheClass_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Get_Instance_Status get_instance(
        TheClass* instance);

    CIMPLE_HIDE Enum_Instance_Status enum_instance(
        TheClass* instance,
        State& state);

    CIMPLE_HIDE Create_Instance_Status create_instance(
        const TheClass* inst);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
        const TheClass* inst);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
        const TheClass* inst);

    CIMPLE_HIDE Invoke_Method_Status add(
        const TheClass* self,
        const Property<uint32>& x,
        const Property<uint32>& y,
        Property<uint32>& return_value);

    static int proc(int operation, void* arg0, void* arg1, void* arg2);
};

CIMPLE_NAMESPACE_END

#endif /* _TheClass_Provider_h */

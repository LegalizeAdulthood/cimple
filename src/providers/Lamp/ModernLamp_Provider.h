#ifndef _ModernLamp_Provider_h
#define _ModernLamp_Provider_h

#include <cimple/cimple.h>
#include "ModernLamp.h"

CIMPLE_NAMESPACE_BEGIN

class ModernLamp_Provider
{
public:

    typedef ModernLamp Class;

    ModernLamp_Provider();

    ~ModernLamp_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const ModernLamp* model,
        ModernLamp*& instance);

    Enum_Instances_Status enum_instances(
        const ModernLamp* model,
        Enum_Instances_Handler<ModernLamp>* handler);

    Create_Instance_Status create_instance(
        const ModernLamp* instance);

    Delete_Instance_Status delete_instance(
        const ModernLamp* instance);

    Modify_Instance_Status modify_instance(
        const ModernLamp* instance);

    Invoke_Method_Status foo(
        const ModernLamp* self,
        const Property<String>& arg1,
        const Property<String>& arg2,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _ModernLamp_Provider_h */

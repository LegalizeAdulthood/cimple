#ifndef _Manager_Provider_h
#define _Manager_Provider_h

#include <cimple/cimple.h>
#include "Manager.h"

CIMPLE_NAMESPACE_BEGIN

class Manager_Provider
{
public:

    typedef Manager Class;

    Manager_Provider();

    ~Manager_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Manager* model,
        Manager*& instance);

    Enum_Instances_Status enum_instances(
        const Manager* model,
        Enum_Instances_Handler<Manager>* handler);

    Create_Instance_Status create_instance(
        Manager* instance);

    Delete_Instance_Status delete_instance(
        const Manager* instance);

    Modify_Instance_Status modify_instance(
        const Manager* model,
        const Manager* instance);

    Invoke_Method_Status SetOutOfOfficeState(
        const Manager* self,
        const Property<boolean>& OutOfOfficeState,
        Property<boolean>& PreviousOutOfOfficeState,
        Property<uint32>& return_value);

    Invoke_Method_Status GetEmployeeCount(
        Property<uint32>& return_value);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Manager_Provider_h */

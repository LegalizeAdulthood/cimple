#ifndef _Employee_Provider_h
#define _Employee_Provider_h

#include <cimple/cimple.h>
#include "Employee.h"

CIMPLE_NAMESPACE_BEGIN

class Employee_Provider
{
public:

    typedef Employee Class;

    Employee_Provider();

    ~Employee_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Employee* model,
        Employee*& instance);

    Enum_Instances_Status enum_instances(
        const Employee* model,
        Enum_Instances_Handler<Employee>* handler);

    Create_Instance_Status create_instance(
        Employee* instance);

    Delete_Instance_Status delete_instance(
        const Employee* instance);

    Modify_Instance_Status modify_instance(
        const Employee* model,
        const Employee* instance);

    Invoke_Method_Status SetOutOfOfficeState(
        const Employee* self,
        const Property<boolean>& OutOfOfficeState,
        Property<boolean>& PreviousOutOfOfficeState,
        Property<uint32>& return_value);

    Invoke_Method_Status GetEmployeeCount(
        Property<uint32>& return_value);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Employee_Provider_h */

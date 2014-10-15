#include "Employee_Provider.h"
#include "Resource.h"

CIMPLE_NAMESPACE_BEGIN

Employee_Provider::Employee_Provider()
{
}

Employee_Provider::~Employee_Provider()
{
}

Load_Status Employee_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Employee_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Employee_Provider::get_instance(
    const Employee* model,
    Employee*& instance)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        Employee* e = resource.employees[i];

        if (key_eq(model, e))
        {
            instance = e->clone();
            return GET_INSTANCE_OK;
        }
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Employee_Provider::enum_instances(
    const Employee* model,
    Enum_Instances_Handler<Employee>* handler)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        Employee* e = resource.employees[i];
        handler->handle(e->clone());
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Employee_Provider::create_instance(
    Employee* instance)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        Employee* e = resource.employees[i];

        if (key_eq(instance, e))
            return CREATE_INSTANCE_DUPLICATE;
    }

    resource.employees.append(instance->clone());
    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status Employee_Provider::delete_instance(
    const Employee* instance)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        Employee* e = resource.employees[i];

        if (key_eq(instance, e))
        {
            resource.employees.remove(i);
            Employee::destroy(e);
            return DELETE_INSTANCE_OK;
        }
    }

    return DELETE_INSTANCE_NOT_FOUND;
}

Modify_Instance_Status Employee_Provider::modify_instance(
    const Employee* model,
    const Employee* instance)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        Employee* e = resource.employees[i];

        if (key_eq(instance, e))
        {
            copy(e, instance, model);
            return MODIFY_INSTANCE_OK;
        }
    }

    return MODIFY_INSTANCE_NOT_FOUND;
}

Invoke_Method_Status Employee_Provider::SetOutOfOfficeState(
    const Employee* self,
    const Property<boolean>& OutOfOfficeState,
    Property<boolean>& PreviousOutOfOfficeState,
    Property<uint32>& return_value)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        Employee* e = resource.employees[i];

        if (key_eq(self, e))
        {
            PreviousOutOfOfficeState = e->OutOfOffice;
            e->OutOfOffice = OutOfOfficeState;
            return_value.set(0);
            return INVOKE_METHOD_OK;
        }
    }

    return_value.set(1);
    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Employee_Provider::GetEmployeeCount(
    Property<uint32>& return_value)
{
    Auto_Mutex am(resource.mutex);

    return_value.set(resource.employees.size());
    return INVOKE_METHOD_OK;
}

/*@END@*/

CIMPLE_NAMESPACE_END

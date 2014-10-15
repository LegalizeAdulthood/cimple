#include "Link_Provider.h"
#include "Employee_Provider.h"
#include "Resource.h"

CIMPLE_NAMESPACE_BEGIN

Link_Provider::Link_Provider()
{
}

Link_Provider::~Link_Provider()
{
}

Load_Status Link_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Link_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Link_Provider::get_instance(
    const Link* model,
    Link*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Link_Provider::enum_instances(
    const Link* model,
    Enum_Instances_Handler<Link>* handler)
{
    Auto_Mutex am(resource.mutex);

    for (size_t i = 0; i < resource.employees.size(); i++)
    {
        const Employee* e = resource.employees[i];

        Employee* emp = Employee::create(true);
        emp->Id = e->Id;

        Manager* mgr = Manager::create(true);
        mgr->Id.set(1001);

        Link* link = Link::create(true);
        link->Mgr = mgr;
        link->Emp = emp;

        handler->handle(link);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Link_Provider::create_instance(
    Link* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Link_Provider::delete_instance(
    const Link* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Link_Provider::modify_instance(
    const Link* model,
    const Link* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status Link_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status Link_Provider::enum_references(
    const Instance* instance,
    const Link* model,
    const String& role,
    Enum_References_Handler<Link>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status Link_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
    Auto_Mutex am(resource.mutex);

    //
    // This function implements the associators operation across the following
    // class.
    //
    //     [Association]
    //     class Link
    //     {
    //         [Key] Employee REF Emp;
    //         [Key] Manager REF Mgr;
    //     };
    //
    // The instance parameter refers to the "source" instance of the 
    // association. This function creates "result" instances and passes
    // them to the handler. If the source is a manager, the results will
    // be employees. If the source is an employee, the result will be
    // a single manager.
    //

    //
    // Client use cases:
    //
    //     $ cimcli a Manager.Id=1001
    //     $ cimcli a Employee.Id=4001
    //

    // Case 1: the source is a manager; results are employees.

    Manager* manager = cast<Manager*>(instance);

    if (manager)
    {
        // The result class must be Employee (or empty).

        if (result_class.size() && result_class != "Employee")
            return ENUM_ASSOCIATORS_FAILED;

        // [Source] role must be "Mgr" or empty.

        if (!role.empty() && !eqi(role, "Mgr"))
            return ENUM_ASSOCIATORS_FAILED;

        // Result_role must be "Emp" or empty.

        if (!result_role.empty() && !eqi(result_role, "Emp"))
            return ENUM_ASSOCIATORS_FAILED;

        // We only have one manager in this module.

        if (manager->Id.value == 1001)
        {
            for (size_t i = 0; i < resource.employees.size(); i++)
                handler->handle(resource.employees[i]->clone());

            return ENUM_ASSOCIATORS_OK;
        }

        return ENUM_ASSOCIATORS_FAILED;
    }

    // Case 2: the source is an employee; result is a manager.

    Employee* employee = cast<Employee*>(instance);

    if (employee)
    {
        // The result class must be Manager (or empty).

        if (result_class.size() && result_class != "Manager")
            return ENUM_ASSOCIATORS_FAILED;

        // [Source] role must be "Emp" or empty.

        if (!role.empty() && !eqi(role, "Emp"))
            return ENUM_ASSOCIATORS_FAILED;

        // Result_role must be "Mgr" or empty.

        if (!result_role.empty() && !eqi(result_role, "Mgr"))
            return ENUM_ASSOCIATORS_FAILED;

        // Find this employee and send result instance.

        for (size_t i = 0; i < resource.employees.size(); i++)
        {
            if (key_eq(resource.employees[i], employee))
            {
                handler->handle(resource.manager->clone());
                return ENUM_ASSOCIATORS_OK;
            }
        }

        return ENUM_ASSOCIATORS_FAILED;
    }

    return ENUM_ASSOCIATORS_FAILED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

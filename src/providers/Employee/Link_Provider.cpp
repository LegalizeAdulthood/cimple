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

CIMPLE_NAMESPACE_END

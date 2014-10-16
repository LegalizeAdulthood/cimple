#include "Upcall3_Provider.h"

#define CIMPLE_PEGASUS_UNSUPPORTED
#include <pegasus/adapter/pegasus_unsupported.h>

CIMPLE_NAMESPACE_BEGIN

static void _enum_CIMComputerSystem()
{
    Pegasus::CIMOMHandle* ch= pegasus::cimom_handle();
    assert(ch != 0);

    Pegasus::OperationContext* oc = pegasus::operation_context();

    try
    {
        Pegasus::Array<Pegasus::CIMInstance> a = ch->enumerateInstances(
            *oc,
            Pegasus::CIMNamespaceName("root/cimv2"),
            Pegasus::CIMName("CIM_ComputerSystem"),
            true,
            false,
            true,
            true,
            Pegasus::CIMPropertyList());

        for (Pegasus::Uint32 i = 0; i < a.size(); i++)
        {
            Pegasus::CString cstr = a[i].getPath().toString().getCString();
            printf("INSTANCES[%s]\n", (const char*)cstr);
        }
    }
    catch (Pegasus::Exception& e)
    {
        Pegasus::CString cstr = e.getMessage().getCString();
        printf("EXCEPTION[%s]\n", (const char*)cstr);
    }
}

Upcall3_Provider::Upcall3_Provider()
{
}

Upcall3_Provider::~Upcall3_Provider()
{
}

Load_Status Upcall3_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Upcall3_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Upcall3_Provider::get_instance(
    const Upcall3* model,
    Upcall3*& instance)
{
    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Upcall3_Provider::enum_instances(
    const Upcall3* model,
    Enum_Instances_Handler<Upcall3> *handler)
{
    _enum_CIMComputerSystem();

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Upcall3_Provider::create_instance(
    const Upcall3* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Upcall3_Provider::delete_instance(
    const Upcall3* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Upcall3_Provider::modify_instance(
    const Upcall3* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status Upcall3_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status Upcall3_Provider::enum_references(
    const Instance* instance,
    const Upcall3* model,
    const String& role,
    Enum_References_Handler<Upcall3>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

int Upcall3_Provider::proc(
    const Registration * registration,
    int operation,
    void *arg0,
    void *arg1,
    void *arg2,
    void *arg3,
    void *arg4,
    void *arg5,
    void *arg6,
    void *arg7)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY
    // GENERATED.

    typedef Upcall3 Class;
    typedef Upcall3_Provider Provider;

    return Association_Provider_Proc_T < Provider >::proc(
        registration,
        operation,
        arg0,
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Upcall3/Upcall3_Provider.cpp,v 1.2 2007/03/07 20:25:29 mbrasher-public Exp $");

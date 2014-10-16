#include "Upcall2_Provider.h"

#define D(X) /* empty */

CIMPLE_NAMESPACE_BEGIN

Upcall2_Provider::Upcall2_Provider()
{
}

Upcall2_Provider::~Upcall2_Provider()
{
}

Load_Status Upcall2_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Upcall2_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Upcall2_Provider::get_instance(
    const Upcall2* model,
    Upcall2*& instance)
{
    Instance_Map<Upcall2> _map;
    _build_map(_map);

    Upcall2 *_instance = _map.lookup(model);

    if (_instance)
    {
        instance = _instance->clone();
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Upcall2_Provider::enum_instances(
    const Upcall2* model,
    Enum_Instances_Handler<Upcall2> *handler)
{
    Instance_Map<Upcall2> _tmpMap;
    {
        Instance_Map<Upcall2> _map;

        // Rebuild Map
        _build_map(_map);

        for (size_t i = 0; i < _map.size(); i++)
            _tmpMap.insert(_map[i]->clone());
    }

    for (size_t i = 0; i < _tmpMap.size(); i++)
        handler->handle(_tmpMap[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Upcall2_Provider::create_instance(
    const Upcall2* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Upcall2_Provider::delete_instance(
    const Upcall2* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Upcall2_Provider::modify_instance(
    const Upcall2* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status Upcall2_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status Upcall2_Provider::enum_references(
    const Instance* instance,
    const Upcall2* model,
    const String& role,
    Enum_References_Handler<Upcall2>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

int Upcall2_Provider::proc(
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

    typedef Upcall2 Class;
    typedef Upcall2_Provider Provider;

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

void Upcall2_Provider::_build_map(Instance_Map<Upcall2>& _map)
{
    char systemName[128];
    strcpy(systemName, "mysystem");

    D( ADPTProvUtil::getSystemName(systemName, sizeof (systemName)); )

    Ref<CIM_ComputerSystem> ccs(CIM_ComputerSystem::create());
    ccs->Name.value = systemName;
    Instance_Enumerator ie;
    Ref<CIM_ComputerSystem> rhcs;

    int found = 0;

    if (cimom::enum_instances("root/ibmsd", ccs.ptr(), ie) == 0)
    {
        for (; ie; ie++)
        {
            rhcs = ie();
            if (rhcs->CreationClassName.value.equal("IBMPSG_ComputerSystem") &&
                rhcs->Name.value.equal("lxpra24337"))
            {
                found = 1;
                break;
            }
        }
    }

#if 0
    if (found)
    {
        if (rhcs)
        {
            Upcall2Part *hhrpInst = Upcall2Part::create();

            D( Upcall2Part_Provider::adptBuildInstance(hhrpInst, true);)
            Upcall2 *ecpInst = Upcall2::create();
            ecpInst->ConformantStandard = hhrpInst;
            ecpInst->ManagedElement = rhcs->clone();
            _map.insert(ecpInst);
        }
    }
#endif
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Upcall2/Upcall2_Provider.cpp,v 1.2 2007/03/07 20:25:29 mbrasher-public Exp $");

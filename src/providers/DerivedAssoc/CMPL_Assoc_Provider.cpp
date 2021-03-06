// Generated by genprov 2.0.8
#include "CMPL_Assoc_Provider.h"
//#include "CMPL_Base_Provider.h"
#include "CMPL_Derived_Provider.h"
#include "CMPL_Other_Provider.h"

CIMPLE_NAMESPACE_BEGIN

#define TRACE

CMPL_Assoc_Provider::CMPL_Assoc_Provider()
{
}

CMPL_Assoc_Provider::~CMPL_Assoc_Provider()
{
}

Load_Status CMPL_Assoc_Provider::load()
{
    TRACE;

    {
        CMPL_Base* antecedent = CMPL_Base::create();
        antecedent->Key.value = 1;
        
        CMPL_Other* dependent = CMPL_Other::create();
        dependent->Key.value = 101;
    
        CMPL_Assoc* cmpl_assoc = CMPL_Assoc::create();
        cmpl_assoc->Antecedent = antecedent;
        cmpl_assoc->Dependant = dependent;
    
        _map.insert(cmpl_assoc);
    }

    {
        CMPL_Derived* antecedent = CMPL_Derived::create();
        antecedent->Key.value = 10;
        
        CMPL_Other* dependent = CMPL_Other::create();
        dependent->Key.value = 101;
    
        CMPL_Assoc* cmpl_assoc = CMPL_Assoc::create();
        cmpl_assoc->Antecedent = cast<CMPL_Base*>(antecedent);
        cmpl_assoc->Dependant = dependent;
    
        _map.insert(cmpl_assoc);
    }
    return LOAD_OK;
}

Unload_Status CMPL_Assoc_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CMPL_Assoc_Provider::get_instance(
    const CMPL_Assoc* model,
    CMPL_Assoc*& instance)
{
    TRACE;
    return _map.get_instance(model, instance);
}

Enum_Instances_Status CMPL_Assoc_Provider::enum_instances(
    const CMPL_Assoc* model,
    Enum_Instances_Handler<CMPL_Assoc>* handler)
{
    TRACE;
    return _map.enum_instances(model, handler);
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CMPL_Assoc_Provider::create_instance(
    CMPL_Assoc* instance)
{
    TRACE;
    return _map.create_instance(instance);
}

Delete_Instance_Status CMPL_Assoc_Provider::delete_instance(
    const CMPL_Assoc* instance)
{
    TRACE;
    return _map.delete_instance(instance);
}

Modify_Instance_Status CMPL_Assoc_Provider::modify_instance(
    const CMPL_Assoc* model,
    const CMPL_Assoc* instance)
{
    TRACE;
    return _map.modify_instance(model, instance);
}

Enum_Associator_Names_Status CMPL_Assoc_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_Associators_Status CMPL_Assoc_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATORS_UNSUPPORTED;
}

Enum_References_Status CMPL_Assoc_Provider::enum_references(
    const Instance* instance,
    const CMPL_Assoc* model,
    const String& role,
    Enum_References_Handler<CMPL_Assoc>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

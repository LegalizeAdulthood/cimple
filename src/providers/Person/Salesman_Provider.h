#ifndef _Salesman_Provider_h
#define _Salesman_Provider_h

#include <cimple/cimple.h>
#include "Salesman.h"

CIMPLE_NAMESPACE_BEGIN

class Salesman_Provider
{
public:

    typedef Salesman Class;

    Salesman_Provider();

    ~Salesman_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Salesman* model,
        Salesman*& instance);

    Enum_Instances_Status enum_instances(
        const Salesman* model,
        Enum_Instances_Handler<Salesman>* handler);

    Create_Instance_Status create_instance(
        Salesman* instance);

    Delete_Instance_Status delete_instance(
        const Salesman* instance);

    Modify_Instance_Status modify_instance(
        const Salesman* model,
        const Salesman* instance);

    Invoke_Method_Status hello(
        const Salesman* self,
        const Property<String>& message,
        Property<String>& response,
        Property<uint32>& return_value);

    /*@END@*/
private:
    Instance_Map<Salesman> _map;
};


CIMPLE_NAMESPACE_END

#endif /* _Salesman_Provider_h */

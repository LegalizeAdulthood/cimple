#ifndef _Benchmark3_Provider_h
#define _Benchmark3_Provider_h

#include <cimple/cimple.h>
#include "Benchmark3.h"

CIMPLE_NAMESPACE_BEGIN

class Benchmark3_Provider
{
public:

    typedef Benchmark3 Class;

    Benchmark3_Provider();

    ~Benchmark3_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Benchmark3* model,
        Benchmark3*& instance);

    Enum_Instances_Status enum_instances(
        const Benchmark3* model,
        Enum_Instances_Handler<Benchmark3>* handler);

    Create_Instance_Status create_instance(
        const Benchmark3* instance);

    Delete_Instance_Status delete_instance(
        const Benchmark3* instance);

    Modify_Instance_Status modify_instance(
        const Benchmark3* instance);

    Invoke_Method_Status IsCompatible(
        const Benchmark3* self,
        const CIM_PhysicalElement* ElementToCheck,
        Property<uint32>& return_value);

    Invoke_Method_Status ConnectorPower(
        const Benchmark3* self,
        const CIM_PhysicalConnector* Connector,
        const Property<boolean>& PoweredOn,
        Property<uint32>& return_value);

    static int proc(
        const Registration* registration,
        int operation, 
        void* arg0, 
        void* arg1, 
        void* arg2, 
        void* arg3,
        void* arg4,
        void* arg5,
        void* arg6,
        void* arg7);

private:

    Array<Benchmark3*> _instances;
};

CIMPLE_NAMESPACE_END

#endif /* _Benchmark3_Provider_h */

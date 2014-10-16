#ifndef _Benchmark1_Provider_h
#define _Benchmark1_Provider_h

#include <cimple/cimple.h>
#include "Benchmark1.h"

CIMPLE_NAMESPACE_BEGIN

class Benchmark1_Provider
{
public:

    typedef Benchmark1 Class;

    Benchmark1_Provider();

    ~Benchmark1_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Benchmark1* model,
        Benchmark1*& instance);

    Enum_Instances_Status enum_instances(
        const Benchmark1* model,
        Enum_Instances_Handler<Benchmark1>* handler);

    Create_Instance_Status create_instance(
        const Benchmark1* instance);

    Delete_Instance_Status delete_instance(
        const Benchmark1* instance);

    Modify_Instance_Status modify_instance(
        const Benchmark1* instance);

    Invoke_Method_Status IsCompatible(
        const Benchmark1* self,
        const CIM_PhysicalElement* ElementToCheck,
        Property<uint32>& return_value);

    Invoke_Method_Status ConnectorPower(
        const Benchmark1* self,
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
};

CIMPLE_NAMESPACE_END

#endif /* _Benchmark1_Provider_h */

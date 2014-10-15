#ifndef _Model_Provider_h
#define _Model_Provider_h

#include <cimple/cimple.h>
#include "Model.h"

CIMPLE_NAMESPACE_BEGIN

class Model_Provider
{
public:

    typedef Model Class;

    Model_Provider();

    CIMPLE_HIDE ~Model_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
        const Model* model,
        Model*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
        const Model* model,
        Enum_Instances_Handler<Model>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
        const Model* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
        const Model* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
        const Model* instance);

    CIMPLE_HIDE Invoke_Method_Status stub(
        const Model* self,
        const Property<String>& w,
        const Property<uint32>& x,
        Property<boolean>& y,
        Property<real32>& z,
        Property<String>& return_value);

    CIMPLE_HIDE Invoke_Method_Status stub2(
        const Property<String>& w,
        const Property<uint32>& x,
        Property<boolean>& y,
        Property<real32>& z,
        Property<String>& return_value);

    static CIMPLE_HIDE int proc(
        int operation, void* arg0, void* arg1, void* arg2, void* arg3);
};

CIMPLE_NAMESPACE_END

#endif /* _Model_Provider_h */

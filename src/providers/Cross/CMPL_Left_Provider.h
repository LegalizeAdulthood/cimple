#ifndef _CMPL_Left_Provider_h
#define _CMPL_Left_Provider_h

#include <cimple/cimple.h>
#include "CMPL_Left.h"

CIMPLE_NAMESPACE_BEGIN

class CMPL_Left_Provider
{
public:

    typedef CMPL_Left Class;

    CMPL_Left_Provider();

    ~CMPL_Left_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const CMPL_Left* model,
        CMPL_Left*& instance);

    Enum_Instances_Status enum_instances(
        const CMPL_Left* model,
        Enum_Instances_Handler<CMPL_Left>* handler);

    Create_Instance_Status create_instance(
        CMPL_Left* instance);

    Delete_Instance_Status delete_instance(
        const CMPL_Left* instance);

    Modify_Instance_Status modify_instance(
        const CMPL_Left* model,
        const CMPL_Left* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _CMPL_Left_Provider_h */

#ifndef _ComputerSystemDiskDrive_Provider_h
#define _ComputerSystemDiskDrive_Provider_h

#include <cimple/cimple.h>
#include "ComputerSystemDiskDrive.h"

CIMPLE_NAMESPACE_BEGIN

class ComputerSystemDiskDrive_Provider
{
public:

    typedef ComputerSystemDiskDrive Class;

    ComputerSystemDiskDrive_Provider();

    ~ComputerSystemDiskDrive_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const ComputerSystemDiskDrive* model,
        ComputerSystemDiskDrive*& instance);

    Enum_Instances_Status enum_instances(
        const ComputerSystemDiskDrive* model,
        Enum_Instances_Handler<ComputerSystemDiskDrive>* handler);

    Create_Instance_Status create_instance(
        ComputerSystemDiskDrive* instance);

    Delete_Instance_Status delete_instance(
        const ComputerSystemDiskDrive* instance);

    Modify_Instance_Status modify_instance(
        const ComputerSystemDiskDrive* model,
        const ComputerSystemDiskDrive* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const ComputerSystemDiskDrive* model,
        const String& role,
        Enum_References_Handler<ComputerSystemDiskDrive>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _ComputerSystemDiskDrive_Provider_h */

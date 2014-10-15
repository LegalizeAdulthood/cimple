#ifndef _Person_Provider_h
#define _Person_Provider_h

#include <cimple/cimple.h>
#include "Person.h"

CIMPLE_NAMESPACE_BEGIN

class Person_Provider
{
public:

    typedef Person Class;

    Person_Provider();

    ~Person_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Person* model, 
        Person*& instance);

    Enum_Instances_Status enum_instances(
        const Person* model, 
        Enum_Instances_Handler<Person>* handler);

    Delete_Instance_Status delete_instance(
        const Person* inst);

    Modify_Instance_Status modify_instance(
        const Person* model,
        const Person* instance);

    Create_Instance_Status create_instance(
        Person* instance);

    /*@END@*/

private:
    Instance_Map<Person> _map;
    Thread _thread;
    Atomic_Counter _stop;
};

CIMPLE_NAMESPACE_END

#endif /* _Person_Provider_h */

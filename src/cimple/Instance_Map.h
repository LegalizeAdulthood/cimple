/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

/**
*   This file defines a container for instances that allows a
    number of general and CIMPLE  specific operations functions
    to be performed against a set of instances in the container.
*   The general functions include:
*       insert an instance
*       find an instance
*       lookup an instance
*       remove an instance
*       clear the entire map
*   To provide support for the CIMPLE instance operations,
*   additional functions are defined so that the user can define
*   access to the map for create, modify, delete, get and
    enumerate instances with a single line of code.
 
    The implementation of this function is a CIMPLE array and
    the lookup/find methods do a linear search of the array.
    Therefore, while this implmenentation produces minimal code
    the lookup can take considerable time on very large arrays.
* 
*   EXAMPLE:
*   The following example manages the operations against a
*   map created during the load operation for the class
*   CMPL_Base. The map is defined in the CMPL_Base_Provider.h
*   file as follows:
*     @END@

    private:
        Instance_Map<CMPL_Base> _map;

*   The following function in the .cpp file creates instances.

         Load_Status CMPL_Base_Provider::load()
        {
            CMPL_Base* instance;
            
            instance = CMPL_Base::create();
            instance->Key.value = 1;
            instance->info.value = "First Instance";
            _map.insert(instance);
        
            instance = CMPL_Base::create();
            instance->Key.value = 2;
            instance->info.value = "Second Instance";
            _map.insert(instance);
            return LOAD_OK;
        }
* 
*       The following implements the get, enum, modify, delete,
*       and create functions for the map defined above
*       Get_Instance_Status CMPL_Base_Provider::get_instance(
            const CMPL_Base* model,
            CMPL_Base*& instance)
        {
*           return _map_get_instance(model, instance);
        }
        Enum_Instances_Status CMPL_Base_Provider::enum_instances(
            const CMPL_Base* model,
            Enum_Instances_Handler<CMPL_Base>* handler)
        {
            TRACE;
            return _map.enum_instances(model, handler);
            return ENUM_INSTANCES_OK;
        }
        
        Create_Instance_Status CMPL_Base_Provider::create_instance(
            CMPL_Base* instance)
        {
            TRACE;
            return _map.create_instance(instance);
        }
        
        Delete_Instance_Status CMPL_Base_Provider::delete_instance(
            const CMPL_Base* instance)
        {
            TRACE;
            return _map.delete_instance(instance);
        }
        
        Modify_Instance_Status CMPL_Base_Provider::modify_instance(
            const CMPL_Base* model,
            const CMPL_Base* instance)
        {
            TRACE;
            return _map.modify_instance(model, instance);
}
*/
#ifndef _cimple_Instance_Map_h
#define _cimple_Instance_Map_h

#include "Meta_Class.h"
#include "Provider.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_CIMPLE_LINKAGE Instance_Map_Base
{
public:

    Instance_Map_Base(const Meta_Class* meta_class);

    ~Instance_Map_Base();

    /**
     * Clear all instances from the map and destroy them
     */
    void clear();

protected:

    size_t _insert(Instance* instance);

    size_t _find(const Instance* instance);

    Instance* _lookup(const Instance* instance);

    void _remove(size_t pos);

    const Meta_Class* _meta_class;

    Array<Instance*> _instances;

    Get_Instance_Status _get_instance(
        const Instance* model, 
        Instance*& instance);

    Enum_Instances_Status _enum_instances(
        const Instance* model,
        Enum_Instances_Proc proc,
        void* client_data);

    Create_Instance_Status _create_instance(
        const Instance* instance);

    Delete_Instance_Status _delete_instance(
        const Instance* instance);

    Modify_Instance_Status _modify_instance(
        const Instance* model,
        const Instance* instance);

    // KS. This should be removed.
    //friend class Load_Provider_Base;
};

template<class CLASS>
class Instance_Map : public Instance_Map_Base
{
public:

    Instance_Map();

    ~Instance_Map();

    /** 
     * Inserts an instance into the map. If an instances is already 
     * in the map (as determined by the map find command), returns 
     * -1
     * 
     * @param instance Instance to be inserted
     * 
     * @return size_t Location where the instance was 
     * inserted. Returns -1 if an instance with the key properties 
     * of the input instance is already in the map. 
     */
    size_t insert(CLASS* instance);

    /**
     * Finds the instance defined by the input parameter in the map.
     * key properties in the input equal to the instance in the map, 
     * constitues equality.   Note that this test does not test 
     * other properties than the key properties. 
     *  
     * @param instance Instance to be compared
     * 
     * @return size_t Location where the instance was 
     * inserted. If no equal instance is found, -1 is returned.
     */ 

    size_t find(const CLASS* instance);

    /** 
     * Returns the instance found if an instance in the map matches 
     * the keys on the input instance 
     * 
     * @param instance Instance to lookup.
     * 
     * @return CLASS* containing the instance if keys match. 
     *         Returns 0 if matching instance not found in the map.
     */
    CLASS* lookup(const CLASS* instance);

    /** 
     * Removes a single instance from the map based on the input 
     * position parameter. If the parameter is out of the range of 
     * the instances in the map, returns without removing any 
     * instance 
     * 
     * @param pos size_t position of instance to remove from the map
     */
    void remove(size_t pos);

    /** 
     * size returns the number of instances in the map
     * 
     * 
     * @return size_t Number of instances in the map
     */
    size_t size() const;

    /** 
     * Return the instance at the position determined by the input 
     * parameter 
     * 
     * @param pos
     * 
     * @return CLASS*
     */
    CLASS* operator[](size_t pos);

    const CLASS* operator[](size_t pos) const;

    /** 
     * Get instance from the map that matches the instance and 
     * model.  This function allows the CIMPLE get_instance(...) 
     * function to directly call a map of instances of the defined 
     * class to get instances. 
     * 
     * @param model - 
     * @param instance - Instance containing the key properties to 
     *        be used to find an instance in the map.
     * 
     * @return Get_Instance_Status
     */
    Get_Instance_Status get_instance(
        const CLASS* model, 
        CLASS*& instance);

    /** 
     * Returns all instances from the map.  This function can be 
     * used directly by the CIMPLE enum_instances functions to get
     * predefined instances from a map. 
     *  
     * 
     * @param model
     * @param handler
     * 
     * @return Enum_Instances_Status. This function returns the same 
     *         status that the a CIMPLE provider writer would
     *         deliver to the server.
     */
    Enum_Instances_Status enum_instances(
        const CLASS* model,
        Enum_Instances_Handler<CLASS>* handler);

    /**
     * Attempts to create the instance in the Instance Map. If the 
     * instance already exists, the correct Create_Instance_Status 
     * is returned indicating that the instance already exists. 
     * 
     * @param instance Instance to be created
     * 
     * @return Create_Instance_Status.  This function returns the same 
     *         status that the a CIMPLE provider writer would
     *         deliver to the server. 
     */
    Create_Instance_Status create_instance(
        const CLASS* instance);

    /**
     * Attempts to delete an instance defined by key properties in 
     * the input parameter in the instance map 
     * 
     * @param instance 
     * 
     * @return Delete_Instance_Status reflecting the results of the 
     *         delete.  If the instance could not be found, returns
     *         the status indication NOT_FOUND 
     */
    Delete_Instance_Status delete_instance(
        const CLASS* instance);

    /**
     * Attempts to modify an instance in the instance map using the 
     * model parameter to locate the instance and the instance 
     * parameter as the basis for the modification.  This method 
     * uses the instance copy function to modify the instance in the 
     * map based on the DMTF instance modification rules. 
     * 
     * @param model  - Instance* defining the keys for the instance 
     *               to be modified
     * @param instance  Instance* containing the properties to be 
     *                  modified.
     * 
     * @return Modify_Instance_Status  Indicating whether the 
     *         modification was successful or not.
     */
    Modify_Instance_Status modify_instance(
        const CLASS* model,
        const CLASS* instance);
};

/**
 * Template defines the constructor for an instance map
 * 
 */
template<class CLASS>
inline Instance_Map<CLASS>::Instance_Map() 
    : Instance_Map_Base(&CLASS::static_meta_class)
{
}

template<class CLASS>
inline Instance_Map<CLASS>::~Instance_Map()
{
}

template<class CLASS>
inline size_t Instance_Map<CLASS>::insert(CLASS* instance)
{
    return _insert(instance);
}

template<class CLASS>
inline size_t Instance_Map<CLASS>::find(const CLASS* instance)
{
    return _find(instance);
}

template<class CLASS>
inline CLASS* Instance_Map<CLASS>::lookup(const CLASS* instance)
{
    return (CLASS*)_lookup(instance);
}

template<class CLASS>
inline void Instance_Map<CLASS>::remove(size_t pos)
{
    _remove(pos);
}

template<class CLASS>
size_t Instance_Map<CLASS>::size() const
{
    return _instances.size();
}

template<class CLASS>
CLASS* Instance_Map<CLASS>::operator[](size_t pos)
{
    return (CLASS*)_instances[pos];
}

template<class CLASS>
const CLASS* Instance_Map<CLASS>::operator[](size_t pos) const
{
    return (CLASS*)_instances[pos];
}

template<class CLASS>
Get_Instance_Status Instance_Map<CLASS>::get_instance(
    const CLASS* model, 
    CLASS*& instance)
{
    return _get_instance((const Instance*)model, (Instance*&)instance);
}

template<class CLASS>
Enum_Instances_Status Instance_Map<CLASS>::enum_instances(
    const CLASS* model,
    Enum_Instances_Handler<CLASS>* handler)
{
    return _enum_instances(
        (const Instance*)model, handler->_proc, handler->_client_data);
}


template<class CLASS>
Create_Instance_Status Instance_Map<CLASS>::create_instance(
    const CLASS* instance)
{
    return _create_instance(instance);
}

template<class CLASS>
Delete_Instance_Status Instance_Map<CLASS>::delete_instance(
    const CLASS* instance)
{
    return _delete_instance(instance);
}

template<class CLASS>
Modify_Instance_Status Instance_Map<CLASS>::modify_instance(
    const CLASS* model,
    const CLASS* instance)
{
    return _modify_instance(model, instance);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Instance_Map<CLASS>_h */

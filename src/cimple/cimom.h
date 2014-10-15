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
/******************************************************************************
    Common interface to the CIMServer upcall interface.  This class provides
    functions for accessing information from the Server including:
    CIM Objects via: operation upcalls.
    Provider control functions such as disallow_unload.
    Additional information that may be available from the server such as
    user name for the operation.

    This CIMPLE interface uses individual provider adapters
    to map the access to each possible interface call.
******************************************************************************/

#ifndef _cimple_cimom_h
#define _cimple_cimom_h

#include "config.h"
#include "Instance.h"
#include "Ref.h"

CIMPLE_NAMESPACE_BEGIN

struct Instance_Enumerator_Rep;

//==============================================================================
//
// Instance_Enumerator
//
//==============================================================================

/** 
 * The Instance_Enumerator allows iterating multi-instance
 * responses received through the upcall  multiobject functions 
 * defined in this header file (ex. enumerates, references, 
 * associators). 
 *  
 * The enumerator returns individual objects as Refs of the 
 * object so that the object can be used locally within the 
 * interation and then is automatically discarded. 
 */

class CIMPLE_CIMPLE_LINKAGE Instance_Enumerator
{
public:

    /** 
     * Constructor for Instance_Enumerator
     * 
     */
    Instance_Enumerator();

    ~Instance_Enumerator();

    /** 
     * boolean return operator to allow enumerations to be 
     * incorporated into condition test statements. 
     * 
     * 
     * @return bool Returns true while there are more elements in 
     * the Enumerator.  Returns false when the enumeration is 
     * complete. 
     *  
     * Example: 
     * \code
     *  Instance_Enumerator ie 
     *  ... instance upcall request with ie.
     * for (; ie; ie ++)
     * {
     *     Ref<Instance> inst = ie();
     *     ... do something with ie
     * }
     * \endcode
     */
    operator bool() const;

    /** 
     *  Increments the iterator to the next item in the iteration
     * 
     */
    void operator++(int);

    /**
     * Returns the Ref of the next CIMPLE instance of the iteration 
     * function return. 
     * 
     * EXAMPLE
     * \code 
     * Instanc_Enumerator ie
     * .... instance upcall
     * for(; ie; ie ++)
     *     Ref<Instance> inst = ie()
     * \endcode
     */
    Ref<Instance> operator()() const;

private:
    Instance_Enumerator(const Instance_Enumerator&);
    Instance_Enumerator& operator=(const Instance_Enumerator&);
    void operator++();
    Instance_Enumerator_Rep* _rep;
    friend struct cimom;
};

//==============================================================================
//
// cimom
//
//==============================================================================

struct CIMPLE_CIMPLE_LINKAGE cimom
{
public:

    /** 
     * Makes an upcall to the server to eunmerate instances for the 
     * namespace and class defined. This is interpreted by each 
     * adapter type to make the request to the server. The 
     * enumerator defines an object that allows enumerating the 
     * response objects. 
     * 
     * @param name_space Namespace for the enumerate
     * @param model Defines the Class for the request
     * @param enumerator Defines the instance enumerator to be used 
     * request returned instances. 
     * 
     * @return int Provides information on the return.  If return
     * = -1 there was an error. If zero the server executed a valid
     * response and the returned instances are available through the
     * enumerator.
     * 
     * Example
     * \code
     *  if (cimom::enum_instances("root/cimv2", model, ie) != 0)
     *      return -1;
     *  for (; ie; ie++)
     *      {
     *          Ref<Instance> inst = ie();
     *          CIM_ComputerSystem* ccs =
     *              cast<CIM_ComputerSystem*>(inst.ptr());
     *          print(ccs);
      *      }
     * \endcode
     */
    static int enum_instances(
        const char* name_space, 
        const Instance* model,
        Instance_Enumerator& enumerator);

    // Not yet implemented
    static int enum_instances(
        const char* name_space, 
        const Instance* model,
        Array<Instance>& instances);
    /** 
     * Make an upcall to the server to get the instance defined by 
     * the model parameter and namespace 
     * 
     * @param name_space Defines the namespace for the operation
     * @param model Defines the object path for the instance to get
     * 
     * @return Ref<Instance>
     */
    static Ref<Instance> get_instance(
        const char* name_space, 
        const Instance* model);

    /** 
     * Make an upcall to the server to create an instance defined by 
     * the model parameter and namespace. 
     * 
     * @param name_space
     * @param instance
     * 
     * @return int
     */
    static int create_instance(
        const char* name_space, 
        const Instance* instance);

    /** 
     * Make an upcall to the server to delete the instance defined 
     * by the model parameter and namespace. 
     * 
     * @param name_space
     * @param instance
     * 
     * @return int
     */
    static int delete_instance(
        const char* name_space, 
        const Instance* instance);

    ///
    static int modify_instance(
        const char* name_space, 
        const Instance* instance);

    /** 
     * Invoke the method defined by the instance and method
     * 
     * @param name_space
     * @param instance
     * @param meth
     * 
     * @return int
     */
    static int invoke_method(
        const char* name_space, 
        const Instance* instance,
        Instance* meth);

    /** 
     * Requests the server to allow or disallow unload of the 
     * provider. 
     * 
     * @param flag. If set to true, the server will allow unload. 
     * If set to false, the server will be requests to disallow 
     * unload. 
     */
    static void allow_unload(bool flag);

    /** 
     * Requests user name information from the server for the 
     * current operation. The actual form that the server provides 
     * this information is protocol dependent but this provides a 
     * common interface for the information.  Note that not all 
     * servers and not all requests provide user name information. 
     * 
     * @param user_name The user name is returned in this variable 
     *                  if the return is true. The returned user
     *                  name may be an empty String.
     * 
     * @return bool If true, there is valid information in the 
     *         user_name.  If false the adapter could not
     *         access/convert the returned information
     * EXPERIMENTAL V 2.05
     */
    static bool get_username(String& user_name);
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_cimom_h */

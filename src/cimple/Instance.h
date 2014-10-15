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
 * Instance is the core of CIMPLE. For the users, instances are 
 * created and manipulated through the templates defined below. 
 * Many of the functions in this file are support functions for 
 * the templates. 
 * Generally, to create an instance of a Class defined in mof 
 * and instantiated through CIMPLE genclass, the user uses the 
 * create method of the CIMPLE_CLASS template. 
 *     #include myClass.h
 *     myClass* myclass = myClass.create(true);
 *  
 * This template includes corresponding methods for clone and 
 * destroy. 
 *  
 * The CIMPLE_METHOD template provides the basis for create, 
 * clone, and destroy for methods. 
 *  
 * Note that many functions are public despite the fact that the 
 * provider writer will probably never neeed them since they are 
 * part of the generation mechanism and support for those parts 
 * of CIMPLE that dynamically manage instances (ex. the 
 * interface adapters). 
 *  
 * Some of the functions that should be used include: 
 *     \li \c key_eq - test for key equality between instances
 *     \li \c identical - compare two instances for equality
 *     \li \c copy - copy non-null properties from one instance
 *     to another instance.
 *     \li \c copy_keys identical to copy except it copies only
 *         key properties
 *     \li \c The cast operator defined below
 */
#ifndef _cimple_Instance_h
#define _cimple_Instance_h

#include "config.h"
#include "Meta_Class.h"
#include "Array.h"
#include "Atomic.h"
#include "Buffer.h"

#define CIMPLE_MAX_REFERENCES_PER_CLASS 16

/*
    CIMPLE_CLASS template that defines the instance manipulation functions for
    the creation, destruction, and clone of instances.  This template class
    is instantiated for the target class in the header file <Classname>.h
    with genprov. genprov creates the CIMPLE Class for the provider defined.
    This defines the create, destroy and clone methods for the CIMPLE class.  
*/
#define CIMPLE_CLASS(CLASS) \
    public: \
        static const Meta_Class static_meta_class; \
        static CLASS* create(bool defaults = false) \
        { \
            return (CLASS*)cimple::create(&CLASS::static_meta_class,defaults); \
        } \
        static void destroy(CLASS* instance) \
        { \
            cimple::destroy(instance); \
        } \
        CLASS* clone() const \
        { \
            return (CLASS*)cimple::clone(this); \
        } \
    private: \
        CLASS() { } \
        ~CLASS() { } \
    public:

#define CIMPLE_METHOD(METHOD) \
    public: \
        static const Meta_Method static_meta_class; \
        static METHOD* create() \
        { \
            return (METHOD*)cimple::create(&METHOD::static_meta_class); \
        } \
        static void destroy(METHOD* instance) \
        { \
            cimple::destroy(instance); \
        } \
        METHOD* clone() const \
        { \
            return (METHOD*)cimple::clone(this); \
        } \
    private: \
        METHOD() { } \
        ~METHOD() { } \
    public:

#define CIMPLE_INSTANCE_MAGIC 0xF00DFACE

CIMPLE_NAMESPACE_BEGIN

struct Meta_Property;

/** Instance is the base class for all generated CIM classes and
 *  CIM method objects. To improve efficiencty and reduce code
 *  size,  it is not designed as a pure object-oriented class
 *  but as a structure with a set of supporting functions. The
 *  function provides the ability to create, destroy, modify,
 *  access internal information, and test intances.
*/
struct CIMPLE_CIMPLE_LINKAGE Instance
{
    uint32 __magic;
    Atomic __refs;
    const Meta_Class* meta_class;
    String __name_space;
    static const Meta_Class static_meta_class;
};

/** Creates an instance from the given meta class. For each property, the 
    null flag is set to false. The caller must eventually pass the new object 
*   to destroy(). Normally this is not called by the user but
*   through the CIMPLE_CLASS template defined above.
*   @param meta_class Meta_Class* pointer to the CIMPLE meta
*                     class from which this instance will be
*                     created
*   @param defaults bool parameter defining whether the complete
*                   instance or only the key properties are
*                   included. If true complete instance is
*                   included.  If false, only key properties are
*                   provided.  
*   @return Instance* The created instance. 
*/
CIMPLE_CIMPLE_LINKAGE
Instance* create(const Meta_Class* meta_class, bool defaults = false);

/** Creates an instance from the given meta method. Sets all null flags to
*   false. The caller must eventually pass the new object to destroy.
*   @param meta_meth Meta_Method* pointer to the CIMPLE meta
*                     meta_method from which this instance will
*                     be created
*   @return Instance* the created instance
*  
*   EXAMPLE:
*   \code
*       SomeClass* inst = SomeClass::create(mc);
*   \endcode
*/
CIMPLE_CIMPLE_LINKAGE
Instance* create(const Meta_Method* meta_meth);

/** Releases all memory held by this instance and then passes it
*   to delete.
*/
CIMPLE_CIMPLE_LINKAGE
void destroy(Instance* instance);

/** Makes an exact copy of the given instance. The caller must eventually pass
*   the new instance to destroy().
*   @param instance Instance* defining the instance to be
*                   cloned.
*   @return Instance* The exact copy of the input instance.
*  
*   EXAMPLE
*   \code
*       Instance* new = clone(oldInstance);
*   \endcode
*/
CIMPLE_CIMPLE_LINKAGE
Instance* clone(const Instance* instance);

/** Similar to clone() but only copies the key fields. The
    caller must eventually pass the new instance to destroy().
*/
CIMPLE_CIMPLE_LINKAGE
Instance* key_clone(const Instance* instance);

/** Returns class name of this instance.
 *  @param instance Instance* pointer to the target instance.
 *  @return char* containing the instance name.
 */
inline const char* class_name_of(const Instance* instance)
{
    return instance->meta_class->name;
}

/** Print this instance to the standard output device. This is
 *  primarily a diagnostic tool.
 *  @param instance Instance* pointer to the instance to be
 *                  printed
 *  @param keys_only bool defines whether the complete instance
 *                   or only keys features will be printed. If
 *                   true only keys will be printed.  This is an
 *                   optional parameter.
 *  \code
 *      ... Class defined for provider is myClass
 *      Instance* myInstance = myClass::create(true);
 *      ... set properties
 *      print(myInstance);
 *  \endcode
*/
CIMPLE_CIMPLE_LINKAGE
void print(const Instance* instance, bool keys_only = false);

/** 
   Print this instance to the defined file output. Only keys are
   printed if the keys_only flag is true. 
 */
CIMPLE_CIMPLE_LINKAGE
void fprint(FILE* os, const Instance* instance, bool keys_only = false);

CIMPLE_CIMPLE_LINKAGE
void __set_null_flags(
    const Instance* inst, bool include_keys, bool include_non_keys, uint8 flag);

inline void nullify_properties(const Instance* inst)
{
    __set_null_flags(inst, true, true, 1);
}

inline void de_nullify_properties(const Instance* inst)
{
    __set_null_flags(inst, true, true, 0);
}

inline void nullify_keys(const Instance* inst)
{
    __set_null_flags(inst, true, false, 1);
}

inline void nullify_non_keys(const Instance* inst)
{
    __set_null_flags(inst, false, true, 1);
}

inline void de_nullify_keys(const Instance* inst)
{
    __set_null_flags(inst, true, false, 0);
}

/** Returns true if the keys in instance1 match the keys in instance2 
*   (i.e., have the same names, types, values, and null
*   fields). The instances can be of different classes.
*   @param instance1
*   @param instance2
*   @return bool true if all key properties match, else false
*/
CIMPLE_CIMPLE_LINKAGE
bool key_eq(const Instance* instance1, const Instance* instance2);

/** Copies all properties of a CIMPLE instance from src to dest.
*/
CIMPLE_CIMPLE_LINKAGE
void copy(Instance* dest, const Instance* src);

/** Copy properties from dest to src, whose features are
 *  non-null in the  model instance. This copy is designed
 *  specifically to support the paradigm for instance updating
 *  of the DMTF CIM modify_instance operation.
 *  
 *  @param dest Instance* that is the destination instance for
 *              non-null properties.
 *  @param src  Instance* that is the source for the copy
 *  @param model Instance* that defines the model for the
 *               operation and defines the valid non-null
 *               properties.
 */
CIMPLE_CIMPLE_LINKAGE
void copy(Instance* dest, const Instance* src, const Instance* model);

/** Copy all key properties from instance1 to instance2.
*/
CIMPLE_CIMPLE_LINKAGE
void copy_keys(Instance* dest, const Instance* src);

/** Returns a pointer to the given property.
*/
inline void* __property_of(Instance* inst, const Meta_Property* mp)
{
    return (uint8*)inst + mp->offset;
}

/** Const version of __property_of().
*/
inline const void* __property_of(const Instance* inst, const Meta_Property* mp)
{
    return __property_of((Instance*)inst, mp);
}

/** Returns a pointer to the given reference.
*/
inline Array_Ref& __array_ref_of(Instance* inst, const Meta_Reference* mr)
{
    return *((Array_Ref*)((uint8*)inst + mr->offset));
}

/** Returns a pointer to the given reference.
*/
inline const Array_Ref& __array_ref_of(
    const Instance* inst, const Meta_Reference* mr)
{
    return *((const Array_Ref*)((uint8*)inst + mr->offset));
}

/** Returns a pointer to the given reference.
*/
inline Instance*& __ref_of(Instance* inst, const Meta_Reference* mr)
{
    return *((Instance**)((uint8*)inst + mr->offset));
}

typedef Array<Instance*> __Reference_Array;

/** Const version of __ref_of().
*/
inline const Instance*& __ref_of( 
    const Instance* inst, const Meta_Reference* mr)
{
    return (const Instance*&)__ref_of((Instance*)inst, mr);
}

/** Compare two instances of the same meta class.
*  @param i1 Instance* to first instance
*  @param i2 Instance* to second instance
*  @return Returns true if the two instances are identical, that
*   is they have the same meta class and the property values.
*/
CIMPLE_CIMPLE_LINKAGE
bool identical(const Instance* i1, const Instance* i2);

/** Finds associators of the instance with respect to the given association 
    instance. Returns the number of associators or negative one
    (-1) if this association instance does not refer to the
    instance at all.
*/
CIMPLE_CIMPLE_LINKAGE
ssize_t get_associators(
    const Instance* instance,
    const Instance* association_instance,
    const char* result_class,
    const char* role,
    const char* result_role,
    const Instance* associators[CIMPLE_MAX_REFERENCES_PER_CLASS]);

/** Returns true if the reference refers to the instance. If role is given,
    then the reference must refer to the instance through a property of
    that name.
*/
CIMPLE_CIMPLE_LINKAGE
bool is_reference_of(
    const Instance* instance,
    const Instance* reference,
    const char* role);

/** Return true if all of the keys are non-null.
*/
CIMPLE_CIMPLE_LINKAGE
bool keys_non_null(const Instance* instance);

/** The is_a operator is used to determine whether an instance
    is a subclass of a given class. For example:

    \code
    Derived* inst = Derived::create();

    if (is_a<Base>(inst))
    {
        // inst is descendant from Base.
    }
    \endcode

    This operator returns false if the instance is not
    descendant from the given class.
*/
template<class CLASS>
struct is_a
{
    explicit is_a(const Instance* inst) : _meta_class(inst->meta_class) { }

    operator bool() 
    { 
        return is_subclass(&CLASS::static_meta_class, _meta_class); 
    }

private:
    const Meta_Class* _meta_class;
};

/** The cast operator performs a dynamic cast from one pointer type to 
    another. It returns non-zero if the instance was in fact an instance of 
    that class.

    For example:

    \code
    Instance* inst = Descendent::create();

    Derived* descendant = cast<Descendent*>(inst);

    if (descendant)
    {
        // inst must refer to an instance of Derived.
    }
    \endcode

    The cast operator returns null if the instance is not in fact an 
    instance of the given class.
*/
template<class CLASS_PTR>
struct cast
{
    explicit cast(const Instance* ptr) : _ptr(ptr) { }

    operator CLASS_PTR()
    {
        if (_ptr && is_subclass(
            &((CLASS_PTR)0)->static_meta_class, _ptr->meta_class))
            return CLASS_PTR(_ptr);

        return 0;
    }

private:
    const Instance* _ptr;
};

CIMPLE_CIMPLE_LINKAGE
void destroyer(Instance* p);

CIMPLE_CIMPLE_LINKAGE
void ref(const Instance* instance);

CIMPLE_CIMPLE_LINKAGE
void unref(const Instance* instance);

/** 
 * Filter the property and reference features of a CIMPLE 
 * instance nullifying those that are not in the propertylist. 
 * If the propertylist is null, all the features are 
 * keptnon-null. If the property list is empty, no properties 
 * are kept non-null. The keepKeys parameter determines if the 
 * key properties may be nullified as part of the operation. 
 * The purpose of this function is normally to filter out 
 * properties that are not part of the CIM operation for those 
 * operations that include a propertylist. 
 * Generally this operation is for the use of the adapters and 
 * the provider writer would not use it. Property filtering for 
 * CIM Operations is the responsibility of each CIMPLE adapter. 
 * For the provider writer to determine the properties that are 
 * required for the response to an operation, the model 
 * parameter can be used.  Those properties that are listed in 
 * an input property list (and all key properties) and set 
 * non-null in the model property. 
 * 
 * @param instance - Instance for which properties are to be 
 *                 filtered
 * @param properties - list of properties to be kept in the 
 *                   instance. All other properties are set NULL
 * @param keepKeys - boolean that determines whether the key 
 *                 properties are to be set in accord with the
 *                 property list or forced to non-null.  If
 *                 true, the key properties are forced to
 *                 non-null.
 * 
 * @return CIMPLE_CIMPLE_LINKAGE int - If zero, 
 */
CIMPLE_CIMPLE_LINKAGE
int filter_properties(Instance* instance, const char* const* properties,
                      boolean keepKeys = true);

// This function parses a CIM model path of the following form to an instance.
//
//     MyClass.key1=value1,key2=value2
//
// It returns a pointer to the newly formed instance. The class that appears
// in the model path must be obtainable (directly or indirectly) from the 
// source_meta_class. Note that all classes within a repository are reachable
// from any given class in that repository since each class has a back pointer
// to an array of all other classes, which is only true if the -r option was
// passed to genclass when the source class was generated.
//
CIMPLE_CIMPLE_LINKAGE
Instance* model_path_to_instance(
    const Meta_Class* source_meta_class, 
    const char* path);

// This function converts an instance to a CIM model path of the following
// form:
//
//     MyClass.key1=value1,key2=value2
//
// It does the reverse of model_path_to_instance() defined above.
//
CIMPLE_CIMPLE_LINKAGE
int instance_to_model_path(
    const Instance* instance, 
    String& model_path);

// Create non-null refs for all ref properties of this instance.
CIMPLE_CIMPLE_LINKAGE
void __create_refs(Instance* inst);

CIMPLE_CIMPLE_LINKAGE
void __print_scalar(FILE* os, uint32 type, const void* ptr);

CIMPLE_CIMPLE_LINKAGE
void __print_array(FILE* os, uint32 type, const void* ptr, size_t depth);

CIMPLE_CIMPLE_LINKAGE
void __print_aux(
    FILE* os,
    const Instance* inst, 
    const char* name, 
    size_t level, 
    bool keys_only);

/** 
 * sets default information into a CIMPLE instance.  Depending 
 * on the clear and defaults parameters this function sets 
 * information into the instance, clears the whole instance and 
 * moves default feature information from the meta-class to the 
 * instnace. 
 * 
 * @param mc - pointer ot the meta-class
 * @param inst - instance to be cleaned
 * @param clear - bool variable that determines if the function 
 *              clears the instance to zero.  If true, the
 *              instance is memset to zero. This also clears the
 *              __name_space variable and sets refs to 1. 
 * @param defaults - bool. If true, default values from the meta 
 *                 class are set into the instance if they are
 *                 non-null. If false, the values are set to
 *                 NULL.
 * 
 * @return CIMPLE_CIMPLE_LINKAGE void
 */
CIMPLE_CIMPLE_LINKAGE
void __default_construct(
    const Meta_Class* mc,
    Instance* inst,
    bool clear,
    bool defaults);

CIMPLE_CIMPLE_LINKAGE
void __destruct(Instance* inst);

CIMPLE_CIMPLE_LINKAGE
void clear(Instance* inst);

// Call func() on every instances reachable from inst (including inst).
CIMPLE_CIMPLE_LINKAGE
void __visit(Instance* inst, void (*func)(Instance*, void*), void* data);

// Set the __name_space member of #inst# and every instance reachable
// from #inst#. Do not change __name_space member if already non-empty,
// unless #force# is true.
CIMPLE_CIMPLE_LINKAGE
void __set_name_space_recursive(
    Instance* inst, 
    const char* name_space, 
    bool force);

CIMPLE_CIMPLE_LINKAGE
int __put_property_from_str(
    Instance* inst,
    const Meta_Property* mp, 
    const char* str);


CIMPLE_NAMESPACE_END


#endif /* _cimple_Instance_h */

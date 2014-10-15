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

#ifndef _cimple_Instance_h
#define _cimple_Instance_h

#include "config.h"
#include "Meta_Class.h"
#include "Array.h"
#include "Atomic.h"

#define CIMPLE_MAX_REFERENCES_PER_CLASS 16

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

/** Base class for all generated CIM classes and CIM method objects.
    Note: sizeof(Instance) == 24 on all platforms.
*/
struct CIMPLE_CIMPLE_LINKAGE Instance
{
    uint32 magic;
    Atomic refs;
    const Meta_Class* meta_class;
    static const Meta_Class static_meta_class;
};

/** Private function to construct a instance.
*/
CIMPLE_CIMPLE_LINKAGE
void __construct(
    const Meta_Class* mc,
    Instance* inst,
    bool clear,
    bool defaults);

/** Creates an instance from the given meta class. For each property, the 
    null flag is set to false. The caller must eventually pass the new object 
    to destroy().
*/
CIMPLE_CIMPLE_LINKAGE
Instance* create(const Meta_Class* meta_class, bool defaults = false);

/** Creates an instance from the given meta method. Sets all null flags to
    false. The caller must eventually pass the new object to destroy.
*/
CIMPLE_CIMPLE_LINKAGE
Instance* create(const Meta_Method* meta_meth);

/** Releases all memory held by this instance and and then passes it to 
    delete.
*/
CIMPLE_CIMPLE_LINKAGE
void destroy(Instance* instance);

/** Makes an exact copy of the given instance. The caller must eventually pass
    the new instance to destroy().
*/
CIMPLE_CIMPLE_LINKAGE
Instance* clone(const Instance* instance);

/** Similar to clone() but only copies over the key fields.
*/
CIMPLE_CIMPLE_LINKAGE
Instance* key_clone(const Instance* instance);

/** Print this instance to the standard output device.
*/
CIMPLE_CIMPLE_LINKAGE
void print(const Instance* instance, bool keys_only = false);

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
    (i.e., have the same names, types, values, and null fields). The 
    instances can be of different classes.
*/
CIMPLE_CIMPLE_LINKAGE
bool key_eq(const Instance* instance1, const Instance* instance2);

/** Copies all properties from instance2 to instance1.
*/
CIMPLE_CIMPLE_LINKAGE
void copy(Instance* instance1, const Instance* instance2);

/** Copy all key properties from instance1 to instance2.
*/
CIMPLE_CIMPLE_LINKAGE
void copy_keys(Instance* instance1, const Instance* instance2);

/** Returns a pointer to the given property.
*/
inline void* property_of(Instance* inst, const Meta_Property* mp)
{
    return (uint8*)inst + mp->offset;
}

/** Const version of property_of().
*/
inline const void* property_of(const Instance* inst, const Meta_Property* mp)
{
    return property_of((Instance*)inst, mp);
}

/** Returns a pointer to the given reference.
*/
inline Instance*& reference_of(Instance* inst, const Meta_Reference* mr)
{
    return *((Instance**)((uint8*)inst + mr->offset));
}

/** Const version of reference_of().
*/
inline const Instance*& reference_of( 
    const Instance* inst, const Meta_Reference* mr)
{
    return (const Instance*&)reference_of((Instance*)inst, mr);
}

/** Returns true if two instances are identical, that is they have the
    same meta class and the property values.
*/
CIMPLE_CIMPLE_LINKAGE
bool identical(const Instance* i1, const Instance* i2);

/** Finds associators of the instance with respect to the given association 
    instance. Returns the number of associators or negative one if this 
    association instance does not refer to the instance at all.
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

/** The is_a operator is used to determine wether an instance is a subclass
    of a given class. For example:

    \code
    Derived* inst = Derived::create();

    if (is_a<Base>(inst))
    {
        // inst is descendant from Base.
    }
    \endcode

    This operator returns false if the instance is not descendant from the given
    class.
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

CIMPLE_CIMPLE_LINKAGE
int filter_properties(Instance* instance, const char* const* properties);

// This function parses a CIM model path of the following form.
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

// This function converts and instance to a CIM model path of the following
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

CIMPLE_NAMESPACE_END

#endif /* _cimple_Instance_h */

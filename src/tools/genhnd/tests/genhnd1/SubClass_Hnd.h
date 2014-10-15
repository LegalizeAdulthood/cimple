//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENHND.
//
//==============================================================================

#ifndef _cimple_SubClass_Hnd
#define _cimple_SubClass_Hnd

#include <cimple/cimple.h>
#include "SubClass.h"
#include "SuperClass_Hnd.h"

CIMPLE_NAMESPACE_BEGIN

class SubClass_Ref : public SuperClass_Ref
{
public:
    typedef SubClass Class;
    SubClass_Ref();
    SubClass_Ref(const SubClass_Ref& x);
    SubClass_Ref(SubClass* inst);
    explicit SubClass_Ref(const Instance_Ref& x);
    ~SubClass_Ref();
    SubClass_Ref& operator=(const SubClass_Ref& x);
    static bool is_a(const Instance_Ref& x);

protected:
    SubClass_Ref(const Meta_Class* mc);
    SubClass_Ref(const Meta_Class* mc, const Instance_Ref& x);
};

class SubClass_Hnd : public SuperClass_Hnd
{
public:
    typedef SubClass Class;
    SubClass_Hnd();
    SubClass_Hnd(const SubClass_Hnd& x);
    SubClass_Hnd(SubClass* inst);
    explicit SubClass_Hnd(const Instance_Hnd& x);
    ~SubClass_Hnd();
    SubClass_Hnd& operator=(const SubClass_Hnd& x);
    static bool is_a(const Instance_Hnd& x);
    SubClass_Ref reference() const;

protected:
    SubClass_Hnd(const Meta_Class* mc);
    SubClass_Hnd(const Meta_Class* mc, const Instance_Hnd& x);
};

inline SubClass_Ref::SubClass_Ref() :
    SuperClass_Ref(&SubClass::static_meta_class)
{
}

inline SubClass_Ref::SubClass_Ref(const SubClass_Ref& x) :
    SuperClass_Ref(x)
{
}

inline SubClass_Ref::SubClass_Ref(SubClass* inst) :
    SuperClass_Ref((SuperClass*)inst)
{
}

inline SubClass_Ref::SubClass_Ref(const Instance_Ref& x) : 
    SuperClass_Ref(&SubClass::static_meta_class, x)
{
}

inline SubClass_Ref::SubClass_Ref(const Meta_Class* mc) : SuperClass_Ref(mc)
{
}

inline SubClass_Ref::SubClass_Ref(const Meta_Class* mc, const Instance_Ref& x) : SuperClass_Ref(mc, x)
{
}

inline SubClass_Ref::~SubClass_Ref()
{
}

inline SubClass_Ref& SubClass_Ref::operator=(const SubClass_Ref& x)
{
    SuperClass_Ref::operator=(x);
    return *this;
}

inline bool SubClass_Ref::is_a(const Instance_Ref& x)
{
    return is_subclass(&SubClass::static_meta_class, x.meta_class());
}

inline SubClass_Hnd::SubClass_Hnd() :
    SuperClass_Hnd(&SubClass::static_meta_class)
{
}

inline SubClass_Hnd::SubClass_Hnd(const SubClass_Hnd& x) :
    SuperClass_Hnd(x)
{
}

inline SubClass_Hnd::SubClass_Hnd(SubClass* inst) :
    SuperClass_Hnd((SuperClass*)inst)
{
}

inline SubClass_Hnd::SubClass_Hnd(const Instance_Hnd& x) : 
    SuperClass_Hnd(&SubClass::static_meta_class, x)
{
}

inline SubClass_Hnd::SubClass_Hnd(const Meta_Class* mc) : SuperClass_Hnd(mc)
{
}

inline SubClass_Hnd::SubClass_Hnd(const Meta_Class* mc, const Instance_Hnd& x) : SuperClass_Hnd(mc, x)
{
}

inline SubClass_Hnd::~SubClass_Hnd()
{
}

inline SubClass_Hnd& SubClass_Hnd::operator=(const SubClass_Hnd& x)
{
    SuperClass_Hnd::operator=(x);
    return *this;
}

inline bool SubClass_Hnd::is_a(const Instance_Hnd& x)
{
    return is_subclass(&SubClass::static_meta_class, x.meta_class());
}

inline SubClass_Ref SubClass_Hnd::reference() const
{
    return SubClass_Ref((SubClass*)key_clone(_inst));
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_SubClass_Hnd_h */

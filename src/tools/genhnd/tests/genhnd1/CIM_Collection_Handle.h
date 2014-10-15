//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_Collection_Handle_h
#define _cimple_CIM_Collection_Handle_h

#include <cimple/cimple.h>
#include "CIM_Collection.h"
#include "CIM_ManagedElement_Handle.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_Collection_Reference : public CIM_ManagedElement_Reference
{
public:

    typedef CIM_Collection Class;
    typedef CIM_Collection_Reference REFERENCE;

    CIM_Collection_Reference();

    CIM_Collection_Reference(const CIM_Collection_Reference& x);

    CIM_Collection_Reference(CIM_Collection* inst);

    template<class CLASS>
    explicit CIM_Collection_Reference(const CLASS& x);

    ~CIM_Collection_Reference();

    CIM_Collection_Reference& operator=(const CIM_Collection_Reference& x);
};

class CIM_Collection_Handle : public CIM_ManagedElement_Handle
{
public:

    typedef CIM_Collection Class;
    typedef CIM_Collection_Reference REFERENCE;

    CIM_Collection_Handle();

    CIM_Collection_Handle(const CIM_Collection_Handle& x);

    CIM_Collection_Handle(CIM_Collection* inst);

    template<class CLASS>
    explicit CIM_Collection_Handle(const CLASS& x);

    ~CIM_Collection_Handle();

    CIM_Collection_Handle& operator=(const CIM_Collection_Handle& x);
};

inline CIM_Collection_Reference::CIM_Collection_Reference()
{
    _inst = CIM_Collection::create(true);
}

inline CIM_Collection_Reference::CIM_Collection_Reference(const CIM_Collection_Reference& x) : CIM_ManagedElement_Reference(x)
{
}

inline CIM_Collection_Reference::CIM_Collection_Reference(CIM_Collection* inst)
{
    _inst = inst;
}

template<class CLASS>
inline CIM_Collection_Reference::CIM_Collection_Reference(const CLASS& x)
{
    _construct(*this, Class::static_meta_class, x);
}

inline CIM_Collection_Reference::~CIM_Collection_Reference()
{
}

inline CIM_Collection_Reference& CIM_Collection_Reference::operator=(const CIM_Collection_Reference& x)
{
    CIM_ManagedElement_Reference::operator=(x);
    return *this;
}

inline CIM_Collection_Handle::CIM_Collection_Handle()
{
    _inst = CIM_Collection::create(true);
}

inline CIM_Collection_Handle::CIM_Collection_Handle(const CIM_Collection_Handle& x) : CIM_ManagedElement_Handle(x)
{
}

inline CIM_Collection_Handle::CIM_Collection_Handle(CIM_Collection* inst)
{
    _inst = inst;
}

template<class CLASS>
inline CIM_Collection_Handle::CIM_Collection_Handle(const CLASS& x)
{
    _construct(*this, Class::static_meta_class, x);
}

inline CIM_Collection_Handle::~CIM_Collection_Handle()
{
}

inline CIM_Collection_Handle& CIM_Collection_Handle::operator=(const CIM_Collection_Handle& x)
{
    CIM_ManagedElement_Handle::operator=(x);
    return *this;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_Collection_Handle_h */

//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENHND.
//
//==============================================================================

#ifndef _cimple_CIM_ComputerSystem_Hnd
#define _cimple_CIM_ComputerSystem_Hnd

#include <cimple/cimple.h>
#include "CIM_ComputerSystem.h"
#include "CIM_System_Hnd.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_ComputerSystem_Ref : public CIM_System_Ref
{
public:
    typedef CIM_ComputerSystem Class;
    CIM_ComputerSystem_Ref();
    CIM_ComputerSystem_Ref(const CIM_ComputerSystem_Ref& x);
    CIM_ComputerSystem_Ref(CIM_ComputerSystem* inst);
    explicit CIM_ComputerSystem_Ref(const Instance_Ref& x);
    ~CIM_ComputerSystem_Ref();
    CIM_ComputerSystem_Ref& operator=(const CIM_ComputerSystem_Ref& x);
    static bool is_a(const Instance_Ref& x);

    Arg<uint32> SetPowerState(
        Ops& __ops,
        const String& __name_space,
        const Arg<uint32>& PowerState,
        const Arg<Datetime>& Time);

protected:
    CIM_ComputerSystem_Ref(const Meta_Class* mc);
    CIM_ComputerSystem_Ref(const Meta_Class* mc, const Instance_Ref& x);
};

class CIM_ComputerSystem_Hnd : public CIM_System_Hnd
{
public:
    typedef CIM_ComputerSystem Class;
    CIM_ComputerSystem_Hnd();
    CIM_ComputerSystem_Hnd(const CIM_ComputerSystem_Hnd& x);
    CIM_ComputerSystem_Hnd(CIM_ComputerSystem* inst);
    explicit CIM_ComputerSystem_Hnd(const Instance_Hnd& x);
    ~CIM_ComputerSystem_Hnd();
    CIM_ComputerSystem_Hnd& operator=(const CIM_ComputerSystem_Hnd& x);
    static bool is_a(const Instance_Hnd& x);
    CIM_ComputerSystem_Ref reference() const;

    // NameFormat:
    const String& NameFormat_value() const;
    void NameFormat_value(const String& x);
    bool NameFormat_null() const;
    void NameFormat_clear();

    // OtherIdentifyingInfo:
    const Array_String& OtherIdentifyingInfo_value() const;
    void OtherIdentifyingInfo_value(const Array_String& x);
    bool OtherIdentifyingInfo_null() const;
    void OtherIdentifyingInfo_clear();

    // IdentifyingDescriptions:
    const Array_String& IdentifyingDescriptions_value() const;
    void IdentifyingDescriptions_value(const Array_String& x);
    bool IdentifyingDescriptions_null() const;
    void IdentifyingDescriptions_clear();

    // Dedicated:
    const Array_uint16& Dedicated_value() const;
    void Dedicated_value(const Array_uint16& x);
    bool Dedicated_null() const;
    void Dedicated_clear();

    // OtherDedicatedDescriptions:
    const Array_String& OtherDedicatedDescriptions_value() const;
    void OtherDedicatedDescriptions_value(const Array_String& x);
    bool OtherDedicatedDescriptions_null() const;
    void OtherDedicatedDescriptions_clear();

    // ResetCapability:
    const uint16& ResetCapability_value() const;
    void ResetCapability_value(const uint16& x);
    bool ResetCapability_null() const;
    void ResetCapability_clear();

    // PowerManagementCapabilities:
    const Array_uint16& PowerManagementCapabilities_value() const;
    void PowerManagementCapabilities_value(const Array_uint16& x);
    bool PowerManagementCapabilities_null() const;
    void PowerManagementCapabilities_clear();

protected:
    CIM_ComputerSystem_Hnd(const Meta_Class* mc);
    CIM_ComputerSystem_Hnd(const Meta_Class* mc, const Instance_Hnd& x);
};

inline CIM_ComputerSystem_Ref::CIM_ComputerSystem_Ref() :
    CIM_System_Ref(&CIM_ComputerSystem::static_meta_class)
{
}

inline CIM_ComputerSystem_Ref::CIM_ComputerSystem_Ref(const CIM_ComputerSystem_Ref& x) :
    CIM_System_Ref(x)
{
}

inline CIM_ComputerSystem_Ref::CIM_ComputerSystem_Ref(CIM_ComputerSystem* inst) :
    CIM_System_Ref((CIM_System*)inst)
{
}

inline CIM_ComputerSystem_Ref::CIM_ComputerSystem_Ref(const Instance_Ref& x) : 
    CIM_System_Ref(&CIM_ComputerSystem::static_meta_class, x)
{
}

inline CIM_ComputerSystem_Ref::CIM_ComputerSystem_Ref(const Meta_Class* mc) : CIM_System_Ref(mc)
{
}

inline CIM_ComputerSystem_Ref::CIM_ComputerSystem_Ref(const Meta_Class* mc, const Instance_Ref& x) : CIM_System_Ref(mc, x)
{
}

inline CIM_ComputerSystem_Ref::~CIM_ComputerSystem_Ref()
{
}

inline CIM_ComputerSystem_Ref& CIM_ComputerSystem_Ref::operator=(const CIM_ComputerSystem_Ref& x)
{
    CIM_System_Ref::operator=(x);
    return *this;
}

inline bool CIM_ComputerSystem_Ref::is_a(const Instance_Ref& x)
{
    return is_subclass(&CIM_ComputerSystem::static_meta_class, x.meta_class());
}

inline Arg<uint32> CIM_ComputerSystem_Ref::SetPowerState(
    Ops& __ops,
    const String& __name_space,
    const Arg<uint32>& PowerState,
    const Arg<Datetime>& Time)
{
    Arg<uint32> __return_value;
    __invoke(
        __ops,
        __name_space,
        *this,
        &CIM_ComputerSystem_SetPowerState_method::static_meta_class,
        &PowerState,
        &Time,
        &__return_value);
    return __return_value;
}

inline CIM_ComputerSystem_Hnd::CIM_ComputerSystem_Hnd() :
    CIM_System_Hnd(&CIM_ComputerSystem::static_meta_class)
{
}

inline CIM_ComputerSystem_Hnd::CIM_ComputerSystem_Hnd(const CIM_ComputerSystem_Hnd& x) :
    CIM_System_Hnd(x)
{
}

inline CIM_ComputerSystem_Hnd::CIM_ComputerSystem_Hnd(CIM_ComputerSystem* inst) :
    CIM_System_Hnd((CIM_System*)inst)
{
}

inline CIM_ComputerSystem_Hnd::CIM_ComputerSystem_Hnd(const Instance_Hnd& x) : 
    CIM_System_Hnd(&CIM_ComputerSystem::static_meta_class, x)
{
}

inline CIM_ComputerSystem_Hnd::CIM_ComputerSystem_Hnd(const Meta_Class* mc) : CIM_System_Hnd(mc)
{
}

inline CIM_ComputerSystem_Hnd::CIM_ComputerSystem_Hnd(const Meta_Class* mc, const Instance_Hnd& x) : CIM_System_Hnd(mc, x)
{
}

inline CIM_ComputerSystem_Hnd::~CIM_ComputerSystem_Hnd()
{
}

inline CIM_ComputerSystem_Hnd& CIM_ComputerSystem_Hnd::operator=(const CIM_ComputerSystem_Hnd& x)
{
    CIM_System_Hnd::operator=(x);
    return *this;
}

inline bool CIM_ComputerSystem_Hnd::is_a(const Instance_Hnd& x)
{
    return is_subclass(&CIM_ComputerSystem::static_meta_class, x.meta_class());
}

inline CIM_ComputerSystem_Ref CIM_ComputerSystem_Hnd::reference() const
{
    return CIM_ComputerSystem_Ref((CIM_ComputerSystem*)key_clone(_inst));
}

inline const String& CIM_ComputerSystem_Hnd::NameFormat_value() const
{
    if (((Class*)_inst)->NameFormat.null)
        _throw_null_access("NameFormat");
   return ((Class*)_inst)->NameFormat.value;
}

inline void CIM_ComputerSystem_Hnd::NameFormat_value(const String& x)
{
    _cow();
   ((Class*)_inst)->NameFormat.value = x;
   ((Class*)_inst)->NameFormat.null = false;
}

inline bool CIM_ComputerSystem_Hnd::NameFormat_null() const
{
   return ((Class*)_inst)->NameFormat.null;
}

inline void CIM_ComputerSystem_Hnd::NameFormat_clear()
{
    _cow();
    __clear(((Class*)_inst)->NameFormat.value);
    ((Class*)_inst)->NameFormat.null = true;;
}

inline const Array_String& CIM_ComputerSystem_Hnd::OtherIdentifyingInfo_value() const
{
    if (((Class*)_inst)->OtherIdentifyingInfo.null)
        _throw_null_access("OtherIdentifyingInfo");
   return ((Class*)_inst)->OtherIdentifyingInfo.value;
}

inline void CIM_ComputerSystem_Hnd::OtherIdentifyingInfo_value(const Array_String& x)
{
    _cow();
   ((Class*)_inst)->OtherIdentifyingInfo.value = x;
   ((Class*)_inst)->OtherIdentifyingInfo.null = false;
}

inline bool CIM_ComputerSystem_Hnd::OtherIdentifyingInfo_null() const
{
   return ((Class*)_inst)->OtherIdentifyingInfo.null;
}

inline void CIM_ComputerSystem_Hnd::OtherIdentifyingInfo_clear()
{
    _cow();
    __clear(((Class*)_inst)->OtherIdentifyingInfo.value);
    ((Class*)_inst)->OtherIdentifyingInfo.null = true;;
}

inline const Array_String& CIM_ComputerSystem_Hnd::IdentifyingDescriptions_value() const
{
    if (((Class*)_inst)->IdentifyingDescriptions.null)
        _throw_null_access("IdentifyingDescriptions");
   return ((Class*)_inst)->IdentifyingDescriptions.value;
}

inline void CIM_ComputerSystem_Hnd::IdentifyingDescriptions_value(const Array_String& x)
{
    _cow();
   ((Class*)_inst)->IdentifyingDescriptions.value = x;
   ((Class*)_inst)->IdentifyingDescriptions.null = false;
}

inline bool CIM_ComputerSystem_Hnd::IdentifyingDescriptions_null() const
{
   return ((Class*)_inst)->IdentifyingDescriptions.null;
}

inline void CIM_ComputerSystem_Hnd::IdentifyingDescriptions_clear()
{
    _cow();
    __clear(((Class*)_inst)->IdentifyingDescriptions.value);
    ((Class*)_inst)->IdentifyingDescriptions.null = true;;
}

inline const Array_uint16& CIM_ComputerSystem_Hnd::Dedicated_value() const
{
    if (((Class*)_inst)->Dedicated.null)
        _throw_null_access("Dedicated");
   return ((Class*)_inst)->Dedicated.value;
}

inline void CIM_ComputerSystem_Hnd::Dedicated_value(const Array_uint16& x)
{
    _cow();
   ((Class*)_inst)->Dedicated.value = x;
   ((Class*)_inst)->Dedicated.null = false;
}

inline bool CIM_ComputerSystem_Hnd::Dedicated_null() const
{
   return ((Class*)_inst)->Dedicated.null;
}

inline void CIM_ComputerSystem_Hnd::Dedicated_clear()
{
    _cow();
    __clear(((Class*)_inst)->Dedicated.value);
    ((Class*)_inst)->Dedicated.null = true;;
}

inline const Array_String& CIM_ComputerSystem_Hnd::OtherDedicatedDescriptions_value() const
{
    if (((Class*)_inst)->OtherDedicatedDescriptions.null)
        _throw_null_access("OtherDedicatedDescriptions");
   return ((Class*)_inst)->OtherDedicatedDescriptions.value;
}

inline void CIM_ComputerSystem_Hnd::OtherDedicatedDescriptions_value(const Array_String& x)
{
    _cow();
   ((Class*)_inst)->OtherDedicatedDescriptions.value = x;
   ((Class*)_inst)->OtherDedicatedDescriptions.null = false;
}

inline bool CIM_ComputerSystem_Hnd::OtherDedicatedDescriptions_null() const
{
   return ((Class*)_inst)->OtherDedicatedDescriptions.null;
}

inline void CIM_ComputerSystem_Hnd::OtherDedicatedDescriptions_clear()
{
    _cow();
    __clear(((Class*)_inst)->OtherDedicatedDescriptions.value);
    ((Class*)_inst)->OtherDedicatedDescriptions.null = true;;
}

inline const uint16& CIM_ComputerSystem_Hnd::ResetCapability_value() const
{
    if (((Class*)_inst)->ResetCapability.null)
        _throw_null_access("ResetCapability");
   return ((Class*)_inst)->ResetCapability.value;
}

inline void CIM_ComputerSystem_Hnd::ResetCapability_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->ResetCapability.value = x;
   ((Class*)_inst)->ResetCapability.null = false;
}

inline bool CIM_ComputerSystem_Hnd::ResetCapability_null() const
{
   return ((Class*)_inst)->ResetCapability.null;
}

inline void CIM_ComputerSystem_Hnd::ResetCapability_clear()
{
    _cow();
    __clear(((Class*)_inst)->ResetCapability.value);
    ((Class*)_inst)->ResetCapability.null = true;;
}

inline const Array_uint16& CIM_ComputerSystem_Hnd::PowerManagementCapabilities_value() const
{
    if (((Class*)_inst)->PowerManagementCapabilities.null)
        _throw_null_access("PowerManagementCapabilities");
   return ((Class*)_inst)->PowerManagementCapabilities.value;
}

inline void CIM_ComputerSystem_Hnd::PowerManagementCapabilities_value(const Array_uint16& x)
{
    _cow();
   ((Class*)_inst)->PowerManagementCapabilities.value = x;
   ((Class*)_inst)->PowerManagementCapabilities.null = false;
}

inline bool CIM_ComputerSystem_Hnd::PowerManagementCapabilities_null() const
{
   return ((Class*)_inst)->PowerManagementCapabilities.null;
}

inline void CIM_ComputerSystem_Hnd::PowerManagementCapabilities_clear()
{
    _cow();
    __clear(((Class*)_inst)->PowerManagementCapabilities.value);
    ((Class*)_inst)->PowerManagementCapabilities.null = true;;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_ComputerSystem_Hnd_h */

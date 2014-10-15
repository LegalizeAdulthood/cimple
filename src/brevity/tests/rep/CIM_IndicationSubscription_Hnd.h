//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENHND.
//
//==============================================================================

#ifndef _cimple_CIM_IndicationSubscription_Hnd
#define _cimple_CIM_IndicationSubscription_Hnd

#include <cimple/cimple.h>
#include "CIM_IndicationSubscription.h"
#include "CIM_IndicationFilter_Hnd.h"
#include "CIM_ListenerDestination_Hnd.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_IndicationSubscription_Ref : public Instance_Ref
{
public:
    typedef CIM_IndicationSubscription Class;
    CIM_IndicationSubscription_Ref();
    CIM_IndicationSubscription_Ref(const CIM_IndicationSubscription_Ref& x);
    CIM_IndicationSubscription_Ref(CIM_IndicationSubscription* inst);
    explicit CIM_IndicationSubscription_Ref(const Instance_Ref& x);
    ~CIM_IndicationSubscription_Ref();
    CIM_IndicationSubscription_Ref& operator=(const CIM_IndicationSubscription_Ref& x);
    static bool is_a(const Instance_Ref& x);

    // Filter:
    CIM_IndicationFilter_Ref Filter_value() const;
    void Filter_value(const CIM_IndicationFilter_Ref& x);
    bool Filter_null() const;
    void Filter_clear();

    // Handler:
    CIM_ListenerDestination_Ref Handler_value() const;
    void Handler_value(const CIM_ListenerDestination_Ref& x);
    bool Handler_null() const;
    void Handler_clear();

protected:
    CIM_IndicationSubscription_Ref(const Meta_Class* mc);
    CIM_IndicationSubscription_Ref(const Meta_Class* mc, const Instance_Ref& x);
};

class CIM_IndicationSubscription_Hnd : public Instance_Hnd
{
public:
    typedef CIM_IndicationSubscription Class;
    CIM_IndicationSubscription_Hnd();
    CIM_IndicationSubscription_Hnd(const CIM_IndicationSubscription_Hnd& x);
    CIM_IndicationSubscription_Hnd(CIM_IndicationSubscription* inst);
    explicit CIM_IndicationSubscription_Hnd(const Instance_Hnd& x);
    ~CIM_IndicationSubscription_Hnd();
    CIM_IndicationSubscription_Hnd& operator=(const CIM_IndicationSubscription_Hnd& x);
    static bool is_a(const Instance_Hnd& x);
    CIM_IndicationSubscription_Ref reference() const;

    // Filter:
    CIM_IndicationFilter_Ref Filter_value() const;
    void Filter_value(const CIM_IndicationFilter_Ref& x);
    bool Filter_null() const;
    void Filter_clear();

    // Handler:
    CIM_ListenerDestination_Ref Handler_value() const;
    void Handler_value(const CIM_ListenerDestination_Ref& x);
    bool Handler_null() const;
    void Handler_clear();

    // OnFatalErrorPolicy:
    const uint16& OnFatalErrorPolicy_value() const;
    void OnFatalErrorPolicy_value(const uint16& x);
    bool OnFatalErrorPolicy_null() const;
    void OnFatalErrorPolicy_clear();

    // OtherOnFatalErrorPolicy:
    const String& OtherOnFatalErrorPolicy_value() const;
    void OtherOnFatalErrorPolicy_value(const String& x);
    bool OtherOnFatalErrorPolicy_null() const;
    void OtherOnFatalErrorPolicy_clear();

    // FailureTriggerTimeInterval:
    const uint64& FailureTriggerTimeInterval_value() const;
    void FailureTriggerTimeInterval_value(const uint64& x);
    bool FailureTriggerTimeInterval_null() const;
    void FailureTriggerTimeInterval_clear();

    // SubscriptionState:
    const uint16& SubscriptionState_value() const;
    void SubscriptionState_value(const uint16& x);
    bool SubscriptionState_null() const;
    void SubscriptionState_clear();

    // OtherSubscriptionState:
    const String& OtherSubscriptionState_value() const;
    void OtherSubscriptionState_value(const String& x);
    bool OtherSubscriptionState_null() const;
    void OtherSubscriptionState_clear();

    // TimeOfLastStateChange:
    const Datetime& TimeOfLastStateChange_value() const;
    void TimeOfLastStateChange_value(const Datetime& x);
    bool TimeOfLastStateChange_null() const;
    void TimeOfLastStateChange_clear();

    // SubscriptionDuration:
    const uint64& SubscriptionDuration_value() const;
    void SubscriptionDuration_value(const uint64& x);
    bool SubscriptionDuration_null() const;
    void SubscriptionDuration_clear();

    // SubscriptionStartTime:
    const Datetime& SubscriptionStartTime_value() const;
    void SubscriptionStartTime_value(const Datetime& x);
    bool SubscriptionStartTime_null() const;
    void SubscriptionStartTime_clear();

    // SubscriptionTimeRemaining:
    const uint64& SubscriptionTimeRemaining_value() const;
    void SubscriptionTimeRemaining_value(const uint64& x);
    bool SubscriptionTimeRemaining_null() const;
    void SubscriptionTimeRemaining_clear();

    // RepeatNotificationPolicy:
    const uint16& RepeatNotificationPolicy_value() const;
    void RepeatNotificationPolicy_value(const uint16& x);
    bool RepeatNotificationPolicy_null() const;
    void RepeatNotificationPolicy_clear();

    // OtherRepeatNotificationPolicy:
    const String& OtherRepeatNotificationPolicy_value() const;
    void OtherRepeatNotificationPolicy_value(const String& x);
    bool OtherRepeatNotificationPolicy_null() const;
    void OtherRepeatNotificationPolicy_clear();

    // RepeatNotificationInterval:
    const uint64& RepeatNotificationInterval_value() const;
    void RepeatNotificationInterval_value(const uint64& x);
    bool RepeatNotificationInterval_null() const;
    void RepeatNotificationInterval_clear();

    // RepeatNotificationGap:
    const uint64& RepeatNotificationGap_value() const;
    void RepeatNotificationGap_value(const uint64& x);
    bool RepeatNotificationGap_null() const;
    void RepeatNotificationGap_clear();

    // RepeatNotificationCount:
    const uint16& RepeatNotificationCount_value() const;
    void RepeatNotificationCount_value(const uint16& x);
    bool RepeatNotificationCount_null() const;
    void RepeatNotificationCount_clear();

protected:
    CIM_IndicationSubscription_Hnd(const Meta_Class* mc);
    CIM_IndicationSubscription_Hnd(const Meta_Class* mc, const Instance_Hnd& x);
};

inline CIM_IndicationSubscription_Ref::CIM_IndicationSubscription_Ref() :
    Instance_Ref(&CIM_IndicationSubscription::static_meta_class)
{
}

inline CIM_IndicationSubscription_Ref::CIM_IndicationSubscription_Ref(const CIM_IndicationSubscription_Ref& x) :
    Instance_Ref(x)
{
}

inline CIM_IndicationSubscription_Ref::CIM_IndicationSubscription_Ref(CIM_IndicationSubscription* inst) :
    Instance_Ref((Instance*)inst)
{
}

inline CIM_IndicationSubscription_Ref::CIM_IndicationSubscription_Ref(const Instance_Ref& x) : 
    Instance_Ref(&CIM_IndicationSubscription::static_meta_class, x)
{
}

inline CIM_IndicationSubscription_Ref::CIM_IndicationSubscription_Ref(const Meta_Class* mc) : Instance_Ref(mc)
{
}

inline CIM_IndicationSubscription_Ref::CIM_IndicationSubscription_Ref(const Meta_Class* mc, const Instance_Ref& x) : Instance_Ref(mc, x)
{
}

inline CIM_IndicationSubscription_Ref::~CIM_IndicationSubscription_Ref()
{
}

inline CIM_IndicationSubscription_Ref& CIM_IndicationSubscription_Ref::operator=(const CIM_IndicationSubscription_Ref& x)
{
    Instance_Ref::operator=(x);
    return *this;
}

inline bool CIM_IndicationSubscription_Ref::is_a(const Instance_Ref& x)
{
    return is_subclass(&CIM_IndicationSubscription::static_meta_class, x.meta_class());
}

inline CIM_IndicationFilter_Ref CIM_IndicationSubscription_Ref::Filter_value() const
{
    if (!((Class*)_inst)->Filter)
        _throw_null_access("Filter");
    ref(((Class*)_inst)->Filter);
    return CIM_IndicationFilter_Ref(((Class*)_inst)->Filter);
}

inline void CIM_IndicationSubscription_Ref::Filter_value(const CIM_IndicationFilter_Ref& x)
{
    _cow();
    unref(((Class*)_inst)->Filter);
    ref(((Class*)_inst)->Filter = (CIM_IndicationFilter*)x.instance());
}

inline bool CIM_IndicationSubscription_Ref::Filter_null() const
{
    return ((Class*)_inst)->Filter == 0;
}

inline void CIM_IndicationSubscription_Ref::Filter_clear()
{
    _cow();
    unref(((Class*)_inst)->Filter);
    ((Class*)_inst)->Filter = 0;
}

inline CIM_ListenerDestination_Ref CIM_IndicationSubscription_Ref::Handler_value() const
{
    if (!((Class*)_inst)->Handler)
        _throw_null_access("Handler");
    ref(((Class*)_inst)->Handler);
    return CIM_ListenerDestination_Ref(((Class*)_inst)->Handler);
}

inline void CIM_IndicationSubscription_Ref::Handler_value(const CIM_ListenerDestination_Ref& x)
{
    _cow();
    unref(((Class*)_inst)->Handler);
    ref(((Class*)_inst)->Handler = (CIM_ListenerDestination*)x.instance());
}

inline bool CIM_IndicationSubscription_Ref::Handler_null() const
{
    return ((Class*)_inst)->Handler == 0;
}

inline void CIM_IndicationSubscription_Ref::Handler_clear()
{
    _cow();
    unref(((Class*)_inst)->Handler);
    ((Class*)_inst)->Handler = 0;
}

inline CIM_IndicationSubscription_Hnd::CIM_IndicationSubscription_Hnd() :
    Instance_Hnd(&CIM_IndicationSubscription::static_meta_class)
{
}

inline CIM_IndicationSubscription_Hnd::CIM_IndicationSubscription_Hnd(const CIM_IndicationSubscription_Hnd& x) :
    Instance_Hnd(x)
{
}

inline CIM_IndicationSubscription_Hnd::CIM_IndicationSubscription_Hnd(CIM_IndicationSubscription* inst) :
    Instance_Hnd((Instance*)inst)
{
}

inline CIM_IndicationSubscription_Hnd::CIM_IndicationSubscription_Hnd(const Instance_Hnd& x) : 
    Instance_Hnd(&CIM_IndicationSubscription::static_meta_class, x)
{
}

inline CIM_IndicationSubscription_Hnd::CIM_IndicationSubscription_Hnd(const Meta_Class* mc) : Instance_Hnd(mc)
{
}

inline CIM_IndicationSubscription_Hnd::CIM_IndicationSubscription_Hnd(const Meta_Class* mc, const Instance_Hnd& x) : Instance_Hnd(mc, x)
{
}

inline CIM_IndicationSubscription_Hnd::~CIM_IndicationSubscription_Hnd()
{
}

inline CIM_IndicationSubscription_Hnd& CIM_IndicationSubscription_Hnd::operator=(const CIM_IndicationSubscription_Hnd& x)
{
    Instance_Hnd::operator=(x);
    return *this;
}

inline bool CIM_IndicationSubscription_Hnd::is_a(const Instance_Hnd& x)
{
    return is_subclass(&CIM_IndicationSubscription::static_meta_class, x.meta_class());
}

inline CIM_IndicationSubscription_Ref CIM_IndicationSubscription_Hnd::reference() const
{
    return CIM_IndicationSubscription_Ref((CIM_IndicationSubscription*)key_clone(_inst));
}

inline CIM_IndicationFilter_Ref CIM_IndicationSubscription_Hnd::Filter_value() const
{
    if (!((Class*)_inst)->Filter)
        _throw_null_access("Filter");
    ref(((Class*)_inst)->Filter);
    return CIM_IndicationFilter_Ref(((Class*)_inst)->Filter);
}

inline void CIM_IndicationSubscription_Hnd::Filter_value(const CIM_IndicationFilter_Ref& x)
{
    _cow();
    unref(((Class*)_inst)->Filter);
    ref(((Class*)_inst)->Filter = (CIM_IndicationFilter*)x.instance());
}

inline bool CIM_IndicationSubscription_Hnd::Filter_null() const
{
    return ((Class*)_inst)->Filter == 0;
}

inline void CIM_IndicationSubscription_Hnd::Filter_clear()
{
    _cow();
    unref(((Class*)_inst)->Filter);
    ((Class*)_inst)->Filter = 0;
}

inline CIM_ListenerDestination_Ref CIM_IndicationSubscription_Hnd::Handler_value() const
{
    if (!((Class*)_inst)->Handler)
        _throw_null_access("Handler");
    ref(((Class*)_inst)->Handler);
    return CIM_ListenerDestination_Ref(((Class*)_inst)->Handler);
}

inline void CIM_IndicationSubscription_Hnd::Handler_value(const CIM_ListenerDestination_Ref& x)
{
    _cow();
    unref(((Class*)_inst)->Handler);
    ref(((Class*)_inst)->Handler = (CIM_ListenerDestination*)x.instance());
}

inline bool CIM_IndicationSubscription_Hnd::Handler_null() const
{
    return ((Class*)_inst)->Handler == 0;
}

inline void CIM_IndicationSubscription_Hnd::Handler_clear()
{
    _cow();
    unref(((Class*)_inst)->Handler);
    ((Class*)_inst)->Handler = 0;
}

inline const uint16& CIM_IndicationSubscription_Hnd::OnFatalErrorPolicy_value() const
{
    if (((Class*)_inst)->OnFatalErrorPolicy.null)
        _throw_null_access("OnFatalErrorPolicy");
   return ((Class*)_inst)->OnFatalErrorPolicy.value;
}

inline void CIM_IndicationSubscription_Hnd::OnFatalErrorPolicy_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->OnFatalErrorPolicy.value = x;
   ((Class*)_inst)->OnFatalErrorPolicy.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::OnFatalErrorPolicy_null() const
{
   return ((Class*)_inst)->OnFatalErrorPolicy.null;
}

inline void CIM_IndicationSubscription_Hnd::OnFatalErrorPolicy_clear()
{
    _cow();
    __clear(((Class*)_inst)->OnFatalErrorPolicy.value);
    ((Class*)_inst)->OnFatalErrorPolicy.null = true;;
}

inline const String& CIM_IndicationSubscription_Hnd::OtherOnFatalErrorPolicy_value() const
{
    if (((Class*)_inst)->OtherOnFatalErrorPolicy.null)
        _throw_null_access("OtherOnFatalErrorPolicy");
   return ((Class*)_inst)->OtherOnFatalErrorPolicy.value;
}

inline void CIM_IndicationSubscription_Hnd::OtherOnFatalErrorPolicy_value(const String& x)
{
    _cow();
   ((Class*)_inst)->OtherOnFatalErrorPolicy.value = x;
   ((Class*)_inst)->OtherOnFatalErrorPolicy.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::OtherOnFatalErrorPolicy_null() const
{
   return ((Class*)_inst)->OtherOnFatalErrorPolicy.null;
}

inline void CIM_IndicationSubscription_Hnd::OtherOnFatalErrorPolicy_clear()
{
    _cow();
    __clear(((Class*)_inst)->OtherOnFatalErrorPolicy.value);
    ((Class*)_inst)->OtherOnFatalErrorPolicy.null = true;;
}

inline const uint64& CIM_IndicationSubscription_Hnd::FailureTriggerTimeInterval_value() const
{
    if (((Class*)_inst)->FailureTriggerTimeInterval.null)
        _throw_null_access("FailureTriggerTimeInterval");
   return ((Class*)_inst)->FailureTriggerTimeInterval.value;
}

inline void CIM_IndicationSubscription_Hnd::FailureTriggerTimeInterval_value(const uint64& x)
{
    _cow();
   ((Class*)_inst)->FailureTriggerTimeInterval.value = x;
   ((Class*)_inst)->FailureTriggerTimeInterval.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::FailureTriggerTimeInterval_null() const
{
   return ((Class*)_inst)->FailureTriggerTimeInterval.null;
}

inline void CIM_IndicationSubscription_Hnd::FailureTriggerTimeInterval_clear()
{
    _cow();
    __clear(((Class*)_inst)->FailureTriggerTimeInterval.value);
    ((Class*)_inst)->FailureTriggerTimeInterval.null = true;;
}

inline const uint16& CIM_IndicationSubscription_Hnd::SubscriptionState_value() const
{
    if (((Class*)_inst)->SubscriptionState.null)
        _throw_null_access("SubscriptionState");
   return ((Class*)_inst)->SubscriptionState.value;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionState_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->SubscriptionState.value = x;
   ((Class*)_inst)->SubscriptionState.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::SubscriptionState_null() const
{
   return ((Class*)_inst)->SubscriptionState.null;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionState_clear()
{
    _cow();
    __clear(((Class*)_inst)->SubscriptionState.value);
    ((Class*)_inst)->SubscriptionState.null = true;;
}

inline const String& CIM_IndicationSubscription_Hnd::OtherSubscriptionState_value() const
{
    if (((Class*)_inst)->OtherSubscriptionState.null)
        _throw_null_access("OtherSubscriptionState");
   return ((Class*)_inst)->OtherSubscriptionState.value;
}

inline void CIM_IndicationSubscription_Hnd::OtherSubscriptionState_value(const String& x)
{
    _cow();
   ((Class*)_inst)->OtherSubscriptionState.value = x;
   ((Class*)_inst)->OtherSubscriptionState.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::OtherSubscriptionState_null() const
{
   return ((Class*)_inst)->OtherSubscriptionState.null;
}

inline void CIM_IndicationSubscription_Hnd::OtherSubscriptionState_clear()
{
    _cow();
    __clear(((Class*)_inst)->OtherSubscriptionState.value);
    ((Class*)_inst)->OtherSubscriptionState.null = true;;
}

inline const Datetime& CIM_IndicationSubscription_Hnd::TimeOfLastStateChange_value() const
{
    if (((Class*)_inst)->TimeOfLastStateChange.null)
        _throw_null_access("TimeOfLastStateChange");
   return ((Class*)_inst)->TimeOfLastStateChange.value;
}

inline void CIM_IndicationSubscription_Hnd::TimeOfLastStateChange_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->TimeOfLastStateChange.value = x;
   ((Class*)_inst)->TimeOfLastStateChange.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::TimeOfLastStateChange_null() const
{
   return ((Class*)_inst)->TimeOfLastStateChange.null;
}

inline void CIM_IndicationSubscription_Hnd::TimeOfLastStateChange_clear()
{
    _cow();
    __clear(((Class*)_inst)->TimeOfLastStateChange.value);
    ((Class*)_inst)->TimeOfLastStateChange.null = true;;
}

inline const uint64& CIM_IndicationSubscription_Hnd::SubscriptionDuration_value() const
{
    if (((Class*)_inst)->SubscriptionDuration.null)
        _throw_null_access("SubscriptionDuration");
   return ((Class*)_inst)->SubscriptionDuration.value;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionDuration_value(const uint64& x)
{
    _cow();
   ((Class*)_inst)->SubscriptionDuration.value = x;
   ((Class*)_inst)->SubscriptionDuration.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::SubscriptionDuration_null() const
{
   return ((Class*)_inst)->SubscriptionDuration.null;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionDuration_clear()
{
    _cow();
    __clear(((Class*)_inst)->SubscriptionDuration.value);
    ((Class*)_inst)->SubscriptionDuration.null = true;;
}

inline const Datetime& CIM_IndicationSubscription_Hnd::SubscriptionStartTime_value() const
{
    if (((Class*)_inst)->SubscriptionStartTime.null)
        _throw_null_access("SubscriptionStartTime");
   return ((Class*)_inst)->SubscriptionStartTime.value;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionStartTime_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->SubscriptionStartTime.value = x;
   ((Class*)_inst)->SubscriptionStartTime.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::SubscriptionStartTime_null() const
{
   return ((Class*)_inst)->SubscriptionStartTime.null;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionStartTime_clear()
{
    _cow();
    __clear(((Class*)_inst)->SubscriptionStartTime.value);
    ((Class*)_inst)->SubscriptionStartTime.null = true;;
}

inline const uint64& CIM_IndicationSubscription_Hnd::SubscriptionTimeRemaining_value() const
{
    if (((Class*)_inst)->SubscriptionTimeRemaining.null)
        _throw_null_access("SubscriptionTimeRemaining");
   return ((Class*)_inst)->SubscriptionTimeRemaining.value;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionTimeRemaining_value(const uint64& x)
{
    _cow();
   ((Class*)_inst)->SubscriptionTimeRemaining.value = x;
   ((Class*)_inst)->SubscriptionTimeRemaining.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::SubscriptionTimeRemaining_null() const
{
   return ((Class*)_inst)->SubscriptionTimeRemaining.null;
}

inline void CIM_IndicationSubscription_Hnd::SubscriptionTimeRemaining_clear()
{
    _cow();
    __clear(((Class*)_inst)->SubscriptionTimeRemaining.value);
    ((Class*)_inst)->SubscriptionTimeRemaining.null = true;;
}

inline const uint16& CIM_IndicationSubscription_Hnd::RepeatNotificationPolicy_value() const
{
    if (((Class*)_inst)->RepeatNotificationPolicy.null)
        _throw_null_access("RepeatNotificationPolicy");
   return ((Class*)_inst)->RepeatNotificationPolicy.value;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationPolicy_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->RepeatNotificationPolicy.value = x;
   ((Class*)_inst)->RepeatNotificationPolicy.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::RepeatNotificationPolicy_null() const
{
   return ((Class*)_inst)->RepeatNotificationPolicy.null;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationPolicy_clear()
{
    _cow();
    __clear(((Class*)_inst)->RepeatNotificationPolicy.value);
    ((Class*)_inst)->RepeatNotificationPolicy.null = true;;
}

inline const String& CIM_IndicationSubscription_Hnd::OtherRepeatNotificationPolicy_value() const
{
    if (((Class*)_inst)->OtherRepeatNotificationPolicy.null)
        _throw_null_access("OtherRepeatNotificationPolicy");
   return ((Class*)_inst)->OtherRepeatNotificationPolicy.value;
}

inline void CIM_IndicationSubscription_Hnd::OtherRepeatNotificationPolicy_value(const String& x)
{
    _cow();
   ((Class*)_inst)->OtherRepeatNotificationPolicy.value = x;
   ((Class*)_inst)->OtherRepeatNotificationPolicy.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::OtherRepeatNotificationPolicy_null() const
{
   return ((Class*)_inst)->OtherRepeatNotificationPolicy.null;
}

inline void CIM_IndicationSubscription_Hnd::OtherRepeatNotificationPolicy_clear()
{
    _cow();
    __clear(((Class*)_inst)->OtherRepeatNotificationPolicy.value);
    ((Class*)_inst)->OtherRepeatNotificationPolicy.null = true;;
}

inline const uint64& CIM_IndicationSubscription_Hnd::RepeatNotificationInterval_value() const
{
    if (((Class*)_inst)->RepeatNotificationInterval.null)
        _throw_null_access("RepeatNotificationInterval");
   return ((Class*)_inst)->RepeatNotificationInterval.value;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationInterval_value(const uint64& x)
{
    _cow();
   ((Class*)_inst)->RepeatNotificationInterval.value = x;
   ((Class*)_inst)->RepeatNotificationInterval.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::RepeatNotificationInterval_null() const
{
   return ((Class*)_inst)->RepeatNotificationInterval.null;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationInterval_clear()
{
    _cow();
    __clear(((Class*)_inst)->RepeatNotificationInterval.value);
    ((Class*)_inst)->RepeatNotificationInterval.null = true;;
}

inline const uint64& CIM_IndicationSubscription_Hnd::RepeatNotificationGap_value() const
{
    if (((Class*)_inst)->RepeatNotificationGap.null)
        _throw_null_access("RepeatNotificationGap");
   return ((Class*)_inst)->RepeatNotificationGap.value;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationGap_value(const uint64& x)
{
    _cow();
   ((Class*)_inst)->RepeatNotificationGap.value = x;
   ((Class*)_inst)->RepeatNotificationGap.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::RepeatNotificationGap_null() const
{
   return ((Class*)_inst)->RepeatNotificationGap.null;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationGap_clear()
{
    _cow();
    __clear(((Class*)_inst)->RepeatNotificationGap.value);
    ((Class*)_inst)->RepeatNotificationGap.null = true;;
}

inline const uint16& CIM_IndicationSubscription_Hnd::RepeatNotificationCount_value() const
{
    if (((Class*)_inst)->RepeatNotificationCount.null)
        _throw_null_access("RepeatNotificationCount");
   return ((Class*)_inst)->RepeatNotificationCount.value;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationCount_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->RepeatNotificationCount.value = x;
   ((Class*)_inst)->RepeatNotificationCount.null = false;
}

inline bool CIM_IndicationSubscription_Hnd::RepeatNotificationCount_null() const
{
   return ((Class*)_inst)->RepeatNotificationCount.null;
}

inline void CIM_IndicationSubscription_Hnd::RepeatNotificationCount_clear()
{
    _cow();
    __clear(((Class*)_inst)->RepeatNotificationCount.value);
    ((Class*)_inst)->RepeatNotificationCount.null = true;;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_IndicationSubscription_Hnd_h */

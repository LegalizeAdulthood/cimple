//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENHND.
//
//==============================================================================

#ifndef _cimple_CIM_Job_Hnd
#define _cimple_CIM_Job_Hnd

#include <cimple/cimple.h>
#include "CIM_Job.h"
#include "CIM_LogicalElement_Hnd.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_Job_Ref : public CIM_LogicalElement_Ref
{
public:
    typedef CIM_Job Class;
    CIM_Job_Ref();
    CIM_Job_Ref(const CIM_Job_Ref& x);
    CIM_Job_Ref(CIM_Job* inst);
    explicit CIM_Job_Ref(const Instance_Ref& x);
    ~CIM_Job_Ref();
    CIM_Job_Ref& operator=(const CIM_Job_Ref& x);
    static bool is_a(const Instance_Ref& x);

    Arg<uint32> KillJob(
        Ops& __ops,
        const String& __name_space,
        const Arg<boolean>& DeleteOnKill);

protected:
    CIM_Job_Ref(const Meta_Class* mc);
    CIM_Job_Ref(const Meta_Class* mc, const Instance_Ref& x);
};

class CIM_Job_Hnd : public CIM_LogicalElement_Hnd
{
public:
    typedef CIM_Job Class;
    CIM_Job_Hnd();
    CIM_Job_Hnd(const CIM_Job_Hnd& x);
    CIM_Job_Hnd(CIM_Job* inst);
    explicit CIM_Job_Hnd(const Instance_Hnd& x);
    ~CIM_Job_Hnd();
    CIM_Job_Hnd& operator=(const CIM_Job_Hnd& x);
    static bool is_a(const Instance_Hnd& x);
    CIM_Job_Ref reference() const;

    // JobStatus:
    const String& JobStatus_value() const;
    void JobStatus_value(const String& x);
    bool JobStatus_null() const;
    void JobStatus_clear();

    // TimeSubmitted:
    const Datetime& TimeSubmitted_value() const;
    void TimeSubmitted_value(const Datetime& x);
    bool TimeSubmitted_null() const;
    void TimeSubmitted_clear();

    // ScheduledStartTime:
    const Datetime& ScheduledStartTime_value() const;
    void ScheduledStartTime_value(const Datetime& x);
    bool ScheduledStartTime_null() const;
    void ScheduledStartTime_clear();

    // StartTime:
    const Datetime& StartTime_value() const;
    void StartTime_value(const Datetime& x);
    bool StartTime_null() const;
    void StartTime_clear();

    // ElapsedTime:
    const Datetime& ElapsedTime_value() const;
    void ElapsedTime_value(const Datetime& x);
    bool ElapsedTime_null() const;
    void ElapsedTime_clear();

    // JobRunTimes:
    const uint32& JobRunTimes_value() const;
    void JobRunTimes_value(const uint32& x);
    bool JobRunTimes_null() const;
    void JobRunTimes_clear();

    // RunMonth:
    const uint8& RunMonth_value() const;
    void RunMonth_value(const uint8& x);
    bool RunMonth_null() const;
    void RunMonth_clear();

    // RunDay:
    const sint8& RunDay_value() const;
    void RunDay_value(const sint8& x);
    bool RunDay_null() const;
    void RunDay_clear();

    // RunDayOfWeek:
    const sint8& RunDayOfWeek_value() const;
    void RunDayOfWeek_value(const sint8& x);
    bool RunDayOfWeek_null() const;
    void RunDayOfWeek_clear();

    // RunStartInterval:
    const Datetime& RunStartInterval_value() const;
    void RunStartInterval_value(const Datetime& x);
    bool RunStartInterval_null() const;
    void RunStartInterval_clear();

    // LocalOrUtcTime:
    const uint16& LocalOrUtcTime_value() const;
    void LocalOrUtcTime_value(const uint16& x);
    bool LocalOrUtcTime_null() const;
    void LocalOrUtcTime_clear();

    // UntilTime:
    const Datetime& UntilTime_value() const;
    void UntilTime_value(const Datetime& x);
    bool UntilTime_null() const;
    void UntilTime_clear();

    // Notify:
    const String& Notify_value() const;
    void Notify_value(const String& x);
    bool Notify_null() const;
    void Notify_clear();

    // Owner:
    const String& Owner_value() const;
    void Owner_value(const String& x);
    bool Owner_null() const;
    void Owner_clear();

    // Priority:
    const uint32& Priority_value() const;
    void Priority_value(const uint32& x);
    bool Priority_null() const;
    void Priority_clear();

    // PercentComplete:
    const uint16& PercentComplete_value() const;
    void PercentComplete_value(const uint16& x);
    bool PercentComplete_null() const;
    void PercentComplete_clear();

    // DeleteOnCompletion:
    const boolean& DeleteOnCompletion_value() const;
    void DeleteOnCompletion_value(const boolean& x);
    bool DeleteOnCompletion_null() const;
    void DeleteOnCompletion_clear();

    // ErrorCode:
    const uint16& ErrorCode_value() const;
    void ErrorCode_value(const uint16& x);
    bool ErrorCode_null() const;
    void ErrorCode_clear();

    // ErrorDescription:
    const String& ErrorDescription_value() const;
    void ErrorDescription_value(const String& x);
    bool ErrorDescription_null() const;
    void ErrorDescription_clear();

    // RecoveryAction:
    const uint16& RecoveryAction_value() const;
    void RecoveryAction_value(const uint16& x);
    bool RecoveryAction_null() const;
    void RecoveryAction_clear();

    // OtherRecoveryAction:
    const String& OtherRecoveryAction_value() const;
    void OtherRecoveryAction_value(const String& x);
    bool OtherRecoveryAction_null() const;
    void OtherRecoveryAction_clear();

protected:
    CIM_Job_Hnd(const Meta_Class* mc);
    CIM_Job_Hnd(const Meta_Class* mc, const Instance_Hnd& x);
};

inline CIM_Job_Ref::CIM_Job_Ref() :
    CIM_LogicalElement_Ref(&CIM_Job::static_meta_class)
{
}

inline CIM_Job_Ref::CIM_Job_Ref(const CIM_Job_Ref& x) :
    CIM_LogicalElement_Ref(x)
{
}

inline CIM_Job_Ref::CIM_Job_Ref(CIM_Job* inst) :
    CIM_LogicalElement_Ref((CIM_LogicalElement*)inst)
{
}

inline CIM_Job_Ref::CIM_Job_Ref(const Instance_Ref& x) : 
    CIM_LogicalElement_Ref(&CIM_Job::static_meta_class, x)
{
}

inline CIM_Job_Ref::CIM_Job_Ref(const Meta_Class* mc) : CIM_LogicalElement_Ref(mc)
{
}

inline CIM_Job_Ref::CIM_Job_Ref(const Meta_Class* mc, const Instance_Ref& x) : CIM_LogicalElement_Ref(mc, x)
{
}

inline CIM_Job_Ref::~CIM_Job_Ref()
{
}

inline CIM_Job_Ref& CIM_Job_Ref::operator=(const CIM_Job_Ref& x)
{
    CIM_LogicalElement_Ref::operator=(x);
    return *this;
}

inline bool CIM_Job_Ref::is_a(const Instance_Ref& x)
{
    return is_subclass(&CIM_Job::static_meta_class, x.meta_class());
}

inline Arg<uint32> CIM_Job_Ref::KillJob(
    Ops& __ops,
    const String& __name_space,
    const Arg<boolean>& DeleteOnKill)
{
    Arg<uint32> __return_value;
    __invoke(
        __ops,
        __name_space,
        *this,
        &CIM_Job_KillJob_method::static_meta_class,
        &DeleteOnKill,
        &__return_value);
    return __return_value;
}

inline CIM_Job_Hnd::CIM_Job_Hnd() :
    CIM_LogicalElement_Hnd(&CIM_Job::static_meta_class)
{
}

inline CIM_Job_Hnd::CIM_Job_Hnd(const CIM_Job_Hnd& x) :
    CIM_LogicalElement_Hnd(x)
{
}

inline CIM_Job_Hnd::CIM_Job_Hnd(CIM_Job* inst) :
    CIM_LogicalElement_Hnd((CIM_LogicalElement*)inst)
{
}

inline CIM_Job_Hnd::CIM_Job_Hnd(const Instance_Hnd& x) : 
    CIM_LogicalElement_Hnd(&CIM_Job::static_meta_class, x)
{
}

inline CIM_Job_Hnd::CIM_Job_Hnd(const Meta_Class* mc) : CIM_LogicalElement_Hnd(mc)
{
}

inline CIM_Job_Hnd::CIM_Job_Hnd(const Meta_Class* mc, const Instance_Hnd& x) : CIM_LogicalElement_Hnd(mc, x)
{
}

inline CIM_Job_Hnd::~CIM_Job_Hnd()
{
}

inline CIM_Job_Hnd& CIM_Job_Hnd::operator=(const CIM_Job_Hnd& x)
{
    CIM_LogicalElement_Hnd::operator=(x);
    return *this;
}

inline bool CIM_Job_Hnd::is_a(const Instance_Hnd& x)
{
    return is_subclass(&CIM_Job::static_meta_class, x.meta_class());
}

inline CIM_Job_Ref CIM_Job_Hnd::reference() const
{
    return CIM_Job_Ref((CIM_Job*)key_clone(_inst));
}

inline const String& CIM_Job_Hnd::JobStatus_value() const
{
    if (((Class*)_inst)->JobStatus.null)
        _throw_null_access("JobStatus");
   return ((Class*)_inst)->JobStatus.value;
}

inline void CIM_Job_Hnd::JobStatus_value(const String& x)
{
    _cow();
   ((Class*)_inst)->JobStatus.value = x;
   ((Class*)_inst)->JobStatus.null = false;
}

inline bool CIM_Job_Hnd::JobStatus_null() const
{
   return ((Class*)_inst)->JobStatus.null;
}

inline void CIM_Job_Hnd::JobStatus_clear()
{
    _cow();
    __clear(((Class*)_inst)->JobStatus.value);
    ((Class*)_inst)->JobStatus.null = true;;
}

inline const Datetime& CIM_Job_Hnd::TimeSubmitted_value() const
{
    if (((Class*)_inst)->TimeSubmitted.null)
        _throw_null_access("TimeSubmitted");
   return ((Class*)_inst)->TimeSubmitted.value;
}

inline void CIM_Job_Hnd::TimeSubmitted_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->TimeSubmitted.value = x;
   ((Class*)_inst)->TimeSubmitted.null = false;
}

inline bool CIM_Job_Hnd::TimeSubmitted_null() const
{
   return ((Class*)_inst)->TimeSubmitted.null;
}

inline void CIM_Job_Hnd::TimeSubmitted_clear()
{
    _cow();
    __clear(((Class*)_inst)->TimeSubmitted.value);
    ((Class*)_inst)->TimeSubmitted.null = true;;
}

inline const Datetime& CIM_Job_Hnd::ScheduledStartTime_value() const
{
    if (((Class*)_inst)->ScheduledStartTime.null)
        _throw_null_access("ScheduledStartTime");
   return ((Class*)_inst)->ScheduledStartTime.value;
}

inline void CIM_Job_Hnd::ScheduledStartTime_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->ScheduledStartTime.value = x;
   ((Class*)_inst)->ScheduledStartTime.null = false;
}

inline bool CIM_Job_Hnd::ScheduledStartTime_null() const
{
   return ((Class*)_inst)->ScheduledStartTime.null;
}

inline void CIM_Job_Hnd::ScheduledStartTime_clear()
{
    _cow();
    __clear(((Class*)_inst)->ScheduledStartTime.value);
    ((Class*)_inst)->ScheduledStartTime.null = true;;
}

inline const Datetime& CIM_Job_Hnd::StartTime_value() const
{
    if (((Class*)_inst)->StartTime.null)
        _throw_null_access("StartTime");
   return ((Class*)_inst)->StartTime.value;
}

inline void CIM_Job_Hnd::StartTime_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->StartTime.value = x;
   ((Class*)_inst)->StartTime.null = false;
}

inline bool CIM_Job_Hnd::StartTime_null() const
{
   return ((Class*)_inst)->StartTime.null;
}

inline void CIM_Job_Hnd::StartTime_clear()
{
    _cow();
    __clear(((Class*)_inst)->StartTime.value);
    ((Class*)_inst)->StartTime.null = true;;
}

inline const Datetime& CIM_Job_Hnd::ElapsedTime_value() const
{
    if (((Class*)_inst)->ElapsedTime.null)
        _throw_null_access("ElapsedTime");
   return ((Class*)_inst)->ElapsedTime.value;
}

inline void CIM_Job_Hnd::ElapsedTime_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->ElapsedTime.value = x;
   ((Class*)_inst)->ElapsedTime.null = false;
}

inline bool CIM_Job_Hnd::ElapsedTime_null() const
{
   return ((Class*)_inst)->ElapsedTime.null;
}

inline void CIM_Job_Hnd::ElapsedTime_clear()
{
    _cow();
    __clear(((Class*)_inst)->ElapsedTime.value);
    ((Class*)_inst)->ElapsedTime.null = true;;
}

inline const uint32& CIM_Job_Hnd::JobRunTimes_value() const
{
    if (((Class*)_inst)->JobRunTimes.null)
        _throw_null_access("JobRunTimes");
   return ((Class*)_inst)->JobRunTimes.value;
}

inline void CIM_Job_Hnd::JobRunTimes_value(const uint32& x)
{
    _cow();
   ((Class*)_inst)->JobRunTimes.value = x;
   ((Class*)_inst)->JobRunTimes.null = false;
}

inline bool CIM_Job_Hnd::JobRunTimes_null() const
{
   return ((Class*)_inst)->JobRunTimes.null;
}

inline void CIM_Job_Hnd::JobRunTimes_clear()
{
    _cow();
    __clear(((Class*)_inst)->JobRunTimes.value);
    ((Class*)_inst)->JobRunTimes.null = true;;
}

inline const uint8& CIM_Job_Hnd::RunMonth_value() const
{
    if (((Class*)_inst)->RunMonth.null)
        _throw_null_access("RunMonth");
   return ((Class*)_inst)->RunMonth.value;
}

inline void CIM_Job_Hnd::RunMonth_value(const uint8& x)
{
    _cow();
   ((Class*)_inst)->RunMonth.value = x;
   ((Class*)_inst)->RunMonth.null = false;
}

inline bool CIM_Job_Hnd::RunMonth_null() const
{
   return ((Class*)_inst)->RunMonth.null;
}

inline void CIM_Job_Hnd::RunMonth_clear()
{
    _cow();
    __clear(((Class*)_inst)->RunMonth.value);
    ((Class*)_inst)->RunMonth.null = true;;
}

inline const sint8& CIM_Job_Hnd::RunDay_value() const
{
    if (((Class*)_inst)->RunDay.null)
        _throw_null_access("RunDay");
   return ((Class*)_inst)->RunDay.value;
}

inline void CIM_Job_Hnd::RunDay_value(const sint8& x)
{
    _cow();
   ((Class*)_inst)->RunDay.value = x;
   ((Class*)_inst)->RunDay.null = false;
}

inline bool CIM_Job_Hnd::RunDay_null() const
{
   return ((Class*)_inst)->RunDay.null;
}

inline void CIM_Job_Hnd::RunDay_clear()
{
    _cow();
    __clear(((Class*)_inst)->RunDay.value);
    ((Class*)_inst)->RunDay.null = true;;
}

inline const sint8& CIM_Job_Hnd::RunDayOfWeek_value() const
{
    if (((Class*)_inst)->RunDayOfWeek.null)
        _throw_null_access("RunDayOfWeek");
   return ((Class*)_inst)->RunDayOfWeek.value;
}

inline void CIM_Job_Hnd::RunDayOfWeek_value(const sint8& x)
{
    _cow();
   ((Class*)_inst)->RunDayOfWeek.value = x;
   ((Class*)_inst)->RunDayOfWeek.null = false;
}

inline bool CIM_Job_Hnd::RunDayOfWeek_null() const
{
   return ((Class*)_inst)->RunDayOfWeek.null;
}

inline void CIM_Job_Hnd::RunDayOfWeek_clear()
{
    _cow();
    __clear(((Class*)_inst)->RunDayOfWeek.value);
    ((Class*)_inst)->RunDayOfWeek.null = true;;
}

inline const Datetime& CIM_Job_Hnd::RunStartInterval_value() const
{
    if (((Class*)_inst)->RunStartInterval.null)
        _throw_null_access("RunStartInterval");
   return ((Class*)_inst)->RunStartInterval.value;
}

inline void CIM_Job_Hnd::RunStartInterval_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->RunStartInterval.value = x;
   ((Class*)_inst)->RunStartInterval.null = false;
}

inline bool CIM_Job_Hnd::RunStartInterval_null() const
{
   return ((Class*)_inst)->RunStartInterval.null;
}

inline void CIM_Job_Hnd::RunStartInterval_clear()
{
    _cow();
    __clear(((Class*)_inst)->RunStartInterval.value);
    ((Class*)_inst)->RunStartInterval.null = true;;
}

inline const uint16& CIM_Job_Hnd::LocalOrUtcTime_value() const
{
    if (((Class*)_inst)->LocalOrUtcTime.null)
        _throw_null_access("LocalOrUtcTime");
   return ((Class*)_inst)->LocalOrUtcTime.value;
}

inline void CIM_Job_Hnd::LocalOrUtcTime_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->LocalOrUtcTime.value = x;
   ((Class*)_inst)->LocalOrUtcTime.null = false;
}

inline bool CIM_Job_Hnd::LocalOrUtcTime_null() const
{
   return ((Class*)_inst)->LocalOrUtcTime.null;
}

inline void CIM_Job_Hnd::LocalOrUtcTime_clear()
{
    _cow();
    __clear(((Class*)_inst)->LocalOrUtcTime.value);
    ((Class*)_inst)->LocalOrUtcTime.null = true;;
}

inline const Datetime& CIM_Job_Hnd::UntilTime_value() const
{
    if (((Class*)_inst)->UntilTime.null)
        _throw_null_access("UntilTime");
   return ((Class*)_inst)->UntilTime.value;
}

inline void CIM_Job_Hnd::UntilTime_value(const Datetime& x)
{
    _cow();
   ((Class*)_inst)->UntilTime.value = x;
   ((Class*)_inst)->UntilTime.null = false;
}

inline bool CIM_Job_Hnd::UntilTime_null() const
{
   return ((Class*)_inst)->UntilTime.null;
}

inline void CIM_Job_Hnd::UntilTime_clear()
{
    _cow();
    __clear(((Class*)_inst)->UntilTime.value);
    ((Class*)_inst)->UntilTime.null = true;;
}

inline const String& CIM_Job_Hnd::Notify_value() const
{
    if (((Class*)_inst)->Notify.null)
        _throw_null_access("Notify");
   return ((Class*)_inst)->Notify.value;
}

inline void CIM_Job_Hnd::Notify_value(const String& x)
{
    _cow();
   ((Class*)_inst)->Notify.value = x;
   ((Class*)_inst)->Notify.null = false;
}

inline bool CIM_Job_Hnd::Notify_null() const
{
   return ((Class*)_inst)->Notify.null;
}

inline void CIM_Job_Hnd::Notify_clear()
{
    _cow();
    __clear(((Class*)_inst)->Notify.value);
    ((Class*)_inst)->Notify.null = true;;
}

inline const String& CIM_Job_Hnd::Owner_value() const
{
    if (((Class*)_inst)->Owner.null)
        _throw_null_access("Owner");
   return ((Class*)_inst)->Owner.value;
}

inline void CIM_Job_Hnd::Owner_value(const String& x)
{
    _cow();
   ((Class*)_inst)->Owner.value = x;
   ((Class*)_inst)->Owner.null = false;
}

inline bool CIM_Job_Hnd::Owner_null() const
{
   return ((Class*)_inst)->Owner.null;
}

inline void CIM_Job_Hnd::Owner_clear()
{
    _cow();
    __clear(((Class*)_inst)->Owner.value);
    ((Class*)_inst)->Owner.null = true;;
}

inline const uint32& CIM_Job_Hnd::Priority_value() const
{
    if (((Class*)_inst)->Priority.null)
        _throw_null_access("Priority");
   return ((Class*)_inst)->Priority.value;
}

inline void CIM_Job_Hnd::Priority_value(const uint32& x)
{
    _cow();
   ((Class*)_inst)->Priority.value = x;
   ((Class*)_inst)->Priority.null = false;
}

inline bool CIM_Job_Hnd::Priority_null() const
{
   return ((Class*)_inst)->Priority.null;
}

inline void CIM_Job_Hnd::Priority_clear()
{
    _cow();
    __clear(((Class*)_inst)->Priority.value);
    ((Class*)_inst)->Priority.null = true;;
}

inline const uint16& CIM_Job_Hnd::PercentComplete_value() const
{
    if (((Class*)_inst)->PercentComplete.null)
        _throw_null_access("PercentComplete");
   return ((Class*)_inst)->PercentComplete.value;
}

inline void CIM_Job_Hnd::PercentComplete_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->PercentComplete.value = x;
   ((Class*)_inst)->PercentComplete.null = false;
}

inline bool CIM_Job_Hnd::PercentComplete_null() const
{
   return ((Class*)_inst)->PercentComplete.null;
}

inline void CIM_Job_Hnd::PercentComplete_clear()
{
    _cow();
    __clear(((Class*)_inst)->PercentComplete.value);
    ((Class*)_inst)->PercentComplete.null = true;;
}

inline const boolean& CIM_Job_Hnd::DeleteOnCompletion_value() const
{
    if (((Class*)_inst)->DeleteOnCompletion.null)
        _throw_null_access("DeleteOnCompletion");
   return ((Class*)_inst)->DeleteOnCompletion.value;
}

inline void CIM_Job_Hnd::DeleteOnCompletion_value(const boolean& x)
{
    _cow();
   ((Class*)_inst)->DeleteOnCompletion.value = x;
   ((Class*)_inst)->DeleteOnCompletion.null = false;
}

inline bool CIM_Job_Hnd::DeleteOnCompletion_null() const
{
   return ((Class*)_inst)->DeleteOnCompletion.null;
}

inline void CIM_Job_Hnd::DeleteOnCompletion_clear()
{
    _cow();
    __clear(((Class*)_inst)->DeleteOnCompletion.value);
    ((Class*)_inst)->DeleteOnCompletion.null = true;;
}

inline const uint16& CIM_Job_Hnd::ErrorCode_value() const
{
    if (((Class*)_inst)->ErrorCode.null)
        _throw_null_access("ErrorCode");
   return ((Class*)_inst)->ErrorCode.value;
}

inline void CIM_Job_Hnd::ErrorCode_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->ErrorCode.value = x;
   ((Class*)_inst)->ErrorCode.null = false;
}

inline bool CIM_Job_Hnd::ErrorCode_null() const
{
   return ((Class*)_inst)->ErrorCode.null;
}

inline void CIM_Job_Hnd::ErrorCode_clear()
{
    _cow();
    __clear(((Class*)_inst)->ErrorCode.value);
    ((Class*)_inst)->ErrorCode.null = true;;
}

inline const String& CIM_Job_Hnd::ErrorDescription_value() const
{
    if (((Class*)_inst)->ErrorDescription.null)
        _throw_null_access("ErrorDescription");
   return ((Class*)_inst)->ErrorDescription.value;
}

inline void CIM_Job_Hnd::ErrorDescription_value(const String& x)
{
    _cow();
   ((Class*)_inst)->ErrorDescription.value = x;
   ((Class*)_inst)->ErrorDescription.null = false;
}

inline bool CIM_Job_Hnd::ErrorDescription_null() const
{
   return ((Class*)_inst)->ErrorDescription.null;
}

inline void CIM_Job_Hnd::ErrorDescription_clear()
{
    _cow();
    __clear(((Class*)_inst)->ErrorDescription.value);
    ((Class*)_inst)->ErrorDescription.null = true;;
}

inline const uint16& CIM_Job_Hnd::RecoveryAction_value() const
{
    if (((Class*)_inst)->RecoveryAction.null)
        _throw_null_access("RecoveryAction");
   return ((Class*)_inst)->RecoveryAction.value;
}

inline void CIM_Job_Hnd::RecoveryAction_value(const uint16& x)
{
    _cow();
   ((Class*)_inst)->RecoveryAction.value = x;
   ((Class*)_inst)->RecoveryAction.null = false;
}

inline bool CIM_Job_Hnd::RecoveryAction_null() const
{
   return ((Class*)_inst)->RecoveryAction.null;
}

inline void CIM_Job_Hnd::RecoveryAction_clear()
{
    _cow();
    __clear(((Class*)_inst)->RecoveryAction.value);
    ((Class*)_inst)->RecoveryAction.null = true;;
}

inline const String& CIM_Job_Hnd::OtherRecoveryAction_value() const
{
    if (((Class*)_inst)->OtherRecoveryAction.null)
        _throw_null_access("OtherRecoveryAction");
   return ((Class*)_inst)->OtherRecoveryAction.value;
}

inline void CIM_Job_Hnd::OtherRecoveryAction_value(const String& x)
{
    _cow();
   ((Class*)_inst)->OtherRecoveryAction.value = x;
   ((Class*)_inst)->OtherRecoveryAction.null = false;
}

inline bool CIM_Job_Hnd::OtherRecoveryAction_null() const
{
   return ((Class*)_inst)->OtherRecoveryAction.null;
}

inline void CIM_Job_Hnd::OtherRecoveryAction_clear()
{
    _cow();
    __clear(((Class*)_inst)->OtherRecoveryAction.value);
    ((Class*)_inst)->OtherRecoveryAction.null = true;;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_Job_Hnd_h */

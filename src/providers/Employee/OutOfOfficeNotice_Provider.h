#ifndef _OutOfOfficeNotice_Provider_h
#define _OutOfOfficeNotice_Provider_h

#include <cimple/cimple.h>
#include "OutOfOfficeNotice.h"

CIMPLE_NAMESPACE_BEGIN

class OutOfOfficeNotice_Provider
{
public:

    typedef OutOfOfficeNotice Class;

    OutOfOfficeNotice_Provider();

    ~OutOfOfficeNotice_Provider();

    Load_Status load();

    Unload_Status unload();

    Enable_Indications_Status enable_indications(
        Indication_Handler<OutOfOfficeNotice>* indication_handler);

    Disable_Indications_Status disable_indications();

private:

    static void* _indication_thread(void* arg);
    Thread _thread;
    Atomic_Counter _continue;

    Indication_Handler<OutOfOfficeNotice>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _OutOfOfficeNotice_Provider_h */

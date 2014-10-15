#include "OutOfOfficeNotice_Provider.h"
#include "Resource.h"

CIMPLE_NAMESPACE_BEGIN

void* OutOfOfficeNotice_Provider::_indication_thread(void* arg)
{
    printf("OutOfOfficeNotice_Provider::_indication_thread()\n");

    OutOfOfficeNotice_Provider* provider = (OutOfOfficeNotice_Provider*)arg;

    while (provider->_continue.get())
    {
        // For each out-of-office employee, send an indication.

        resource.mutex.lock();

        for (size_t i = 0; i < resource.employees.size(); i++)
        {
            const Employee* e = resource.employees[i];

            if (e->OutOfOffice.value)
            {
                OutOfOfficeNotice* notice = OutOfOfficeNotice::create(true);
                notice->employee = clone(e);
                provider->_indication_handler->handle(notice);
            }
        }

        resource.mutex.unlock();

        Time::sleep(1 * Time::SEC);
    }

    return 0;
}

OutOfOfficeNotice_Provider::OutOfOfficeNotice_Provider() : 
    _indication_handler(0)
{
}

OutOfOfficeNotice_Provider::~OutOfOfficeNotice_Provider()
{
}

Load_Status OutOfOfficeNotice_Provider::load()
{
    return LOAD_OK;
}

Unload_Status OutOfOfficeNotice_Provider::unload()
{
    return UNLOAD_OK;
}

Enable_Indications_Status OutOfOfficeNotice_Provider::enable_indications(
    Indication_Handler<OutOfOfficeNotice>* indication_handler)
{
    // Save indication handler.
    _indication_handler = indication_handler;

    // Create indication thread.
    _continue.inc();
    Thread::create_joinable(_thread, (Thread_Proc)_indication_thread, this);

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status OutOfOfficeNotice_Provider::disable_indications()
{
    // Destroy indication thread.
    _continue.dec();
    void* value_ptr;
    Thread::join(_thread, value_ptr);

    // Delete indication handler.
    delete _indication_handler;
    _indication_handler = 0;

    return DISABLE_INDICATIONS_OK;
}

CIMPLE_NAMESPACE_END

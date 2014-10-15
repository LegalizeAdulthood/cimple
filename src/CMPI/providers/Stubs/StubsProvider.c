/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include <string.h>
#include <time.h>
#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"

static const CMPIBroker * _broker;

CMPIStatus StubsProviderCleanup(
    CMPIInstanceMI* self, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    printf("==== StubsProviderCleanup()\n");
    CMReturn(CMPI_RC_OK);
}

static CMPIStatus StubsProviderEnumInstanceNames(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref)
{
    printf("==== StubsProviderEnumInstanceNames()\n");

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

static CMPIStatus StubsProviderEnumInstances(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const char** properties)
{
    printf("==== StubsProviderEnumInstances()\n");

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

static CMPIStatus StubsProviderGetInstance(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const char** properties)
{
    printf("==== StubsProviderGetInstance()\n");

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

static CMPIStatus StubsProviderCreateInstance(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const CMPIInstance* inst)
{
    printf ("==== StubsProviderCreateInstance()\n");

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

static CMPIStatus StubsProviderModifyInstance(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const CMPIInstance* inst,
    const char** properties)
{
    printf ("==== StubsProviderModifyInstance()\n");

    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus StubsProviderDeleteInstance(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref)
{
    printf ("==== StubsProviderDeleteInstance()\n");

    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus StubsProviderExecQuery(
    CMPIInstanceMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const char* lang, 
    const char* query)
{
    printf ("==== StubsProviderExecQuery()\n");

    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus StubsProviderMethodCleanup(
    CMPIMethodMI* self, 
    const CMPIContext* context,
    CMPIBoolean terminating)
{
    CMReturn(CMPI_RC_OK);
}

static CMPIStatus StubsProviderInvokeMethod(
    CMPIMethodMI* self, 
    const CMPIContext* context, 
    const CMPIResult* result,
    const CMPIObjectPath* ref, 
    const char* method, 
    const CMPIArgs* in,
    CMPIArgs* out)
{
    printf("==== StubsProviderInvokeMethod()\n");

    CMReturnDone(result);
    CMReturn(CMPI_RC_OK);
}

CMInstanceMIStub(StubsProvider, StubsProvider, _broker, CMNoHook);
CMMethodMIStub(StubsProvider, StubsProvider, _broker, CMNoHook);

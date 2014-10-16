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

#ifndef CIMPLE_Provider_Manager_h
#define CIMPLE_Provider_Manager_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/ProviderManager2/ProviderManager.h>
#include <disp/Dispatcher.h>
#include "Subscription.h"

PEGASUS_NAMESPACE_BEGIN

class CIMPLE_HIDE CIMPLE_Provider_Manager : public ProviderManager
{
public:

    CIMPLE_Provider_Manager();

    virtual ~CIMPLE_Provider_Manager();

    virtual Message* processMessage(Message* request);

    virtual Boolean hasActiveProviders();

    virtual void unloadIdleProviders();

private:

    Message* _handleInitializeProviderRequest(Message*);
    Message* _handleGetInstanceRequest(Message*);
    Message* _handleEnumerateInstancesRequest(Message*);
    Message* _handleEnumerateInstanceNamesRequest(Message*);
    Message* _handleCreateInstanceRequest(Message*);
    Message* _handleModifyInstanceRequest(Message*);
    Message* _handleDeleteInstanceRequest(Message*);
    Message* _handleExecQueryRequest(Message*);
    Message* _handleAssociatorsRequest(Message*);
    Message* _handleAssociatorNamesRequest(Message*);
    Message* _handleReferencesRequest(Message*);
    Message* _handleReferenceNamesRequest(Message*);
    Message* _handleInvokeMethodRequest(Message*);
    Message* _handleGetPropertyRequest(Message*);
    Message* _handleSetPropertyRequest(Message*);
    Message* _handleCreateSubscriptionRequest(Message*);
    Message* _handleModifySubscriptionRequest(Message*);
    Message* _handleDeleteSubscriptionRequest(Message*);
    Message* _handleExportIndicationRequest(Message*);
    Message* _handleDisableModuleRequest(Message*);
    Message* _handleEnableModuleRequest(Message*);
    Message* _handleStopAllProvidersRequest(Message*);
    Message* _handleSubscriptionInitCompleteRequest(Message*);

    void _create_disp(Message* message);

    int _enable_indications(
        Subscription* sub);

    cimple::Dispatcher* _disp;

    Subscription_List _subscription_list;
};

PEGASUS_NAMESPACE_END

#endif /* CIMPLE_Provider_Manager_h */

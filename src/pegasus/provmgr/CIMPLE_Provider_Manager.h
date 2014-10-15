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

#ifndef CIMPLE_Provider_Manager_h
#define CIMPLE_Provider_Manager_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/ProviderManager2/ProviderManager.h>
#include <disp/Dispatcher.h>
#include "Subscription.h"

PEGASUS_NAMESPACE_BEGIN

class CIMPLE_Provider_Manager : public ProviderManager
{
public:

    CIMPLE_Provider_Manager();

    virtual ~CIMPLE_Provider_Manager();

    virtual Message* processMessage(Message* request);

    virtual Boolean hasActiveProviders();

    virtual void unloadIdleProviders();

private:

    CIMPLE_HIDE Message* _handleInitializeProviderRequest(Message*);
    CIMPLE_HIDE Message* _handleGetInstanceRequest(Message*);
    CIMPLE_HIDE Message* _handleEnumerateInstancesRequest(Message*);
    CIMPLE_HIDE Message* _handleEnumerateInstanceNamesRequest(Message*);
    CIMPLE_HIDE Message* _handleCreateInstanceRequest(Message*);
    CIMPLE_HIDE Message* _handleModifyInstanceRequest(Message*);
    CIMPLE_HIDE Message* _handleDeleteInstanceRequest(Message*);
    CIMPLE_HIDE Message* _handleExecQueryRequest(Message*);
    CIMPLE_HIDE Message* _handleAssociatorsRequest(Message*);
    CIMPLE_HIDE Message* _handleAssociatorNamesRequest(Message*);
    CIMPLE_HIDE Message* _handleReferencesRequest(Message*);
    CIMPLE_HIDE Message* _handleReferenceNamesRequest(Message*);
    CIMPLE_HIDE Message* _handleInvokeMethodRequest(Message*);
    CIMPLE_HIDE Message* _handleGetPropertyRequest(Message*);
    CIMPLE_HIDE Message* _handleSetPropertyRequest(Message*);
    CIMPLE_HIDE Message* _handleCreateSubscriptionRequest(Message*);
    CIMPLE_HIDE Message* _handleModifySubscriptionRequest(Message*);
    CIMPLE_HIDE Message* _handleDeleteSubscriptionRequest(Message*);
    CIMPLE_HIDE Message* _handleExportIndicationRequest(Message*);
    CIMPLE_HIDE Message* _handleDisableModuleRequest(Message*);
    CIMPLE_HIDE Message* _handleEnableModuleRequest(Message*);
    CIMPLE_HIDE Message* _handleStopAllProvidersRequest(Message*);
    CIMPLE_HIDE Message* _handleSubscriptionInitCompleteRequest(Message*);

    CIMPLE_HIDE void _create_disp(Message* message);

    CIMPLE_HIDE int _enable_indications(
	Subscription* sub);

    cimple::Dispatcher* _disp;

    Subscription_List _subscription_list;
};

PEGASUS_NAMESPACE_END

#endif /* CIMPLE_Provider_Manager_h */

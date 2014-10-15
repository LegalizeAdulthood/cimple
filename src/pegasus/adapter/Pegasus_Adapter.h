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

#ifndef _cimple_Pegasus_Adapter_h
#define _cimple_Pegasus_Adapter_h

#include <cimple/cimple.h>
#include <pegasus/utils/pegasus.h>

CIMPLE_NAMESPACE_BEGIN

class Provider_Handle;

class CIMPLE_HIDE Pegasus_Adapter : 
    public Pegasus::CIMMethodProvider, 
    public Pegasus::CIMInstanceProvider,
    public Pegasus::CIMAssociationProvider,
    public Pegasus::CIMIndicationProvider
{
public:

    Pegasus_Adapter(Provider_Handle* handle);

    virtual ~Pegasus_Adapter();

    virtual void initialize(Pegasus::CIMOMHandle& cimom);

    virtual void terminate(void);

    virtual void getInstance(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
        Pegasus::InstanceResponseHandler& handler);

    virtual void enumerateInstances(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
        Pegasus::InstanceResponseHandler& handler);

    virtual void enumerateInstanceNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual void modifyInstance(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::CIMInstance& instance,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::CIMPropertyList& propertyList,
        Pegasus::ResponseHandler& handler);

    virtual void createInstance(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::CIMInstance& instance,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual void deleteInstance(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        Pegasus::ResponseHandler& handler);

    virtual void invokeMethod(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectPath,
        const Pegasus::CIMName& methodName,
        const Pegasus::Array<Pegasus::CIMParamValue>& inParameters,
        Pegasus::MethodResultResponseHandler& handler);

    virtual void associators(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& associationClass,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        const Pegasus::String& resultRole,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
        Pegasus::ObjectResponseHandler& handler);

    virtual void associatorNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& associationClass,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        const Pegasus::String& resultRole,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual void references(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        const Pegasus::Boolean includeQualifiers,
        const Pegasus::Boolean includeClassOrigin,
        const Pegasus::CIMPropertyList& propertyList,
        Pegasus::ObjectResponseHandler& handler);

    virtual void referenceNames(
        const Pegasus::OperationContext& context,
        const Pegasus::CIMObjectPath& objectName,
        const Pegasus::CIMName& resultClass,
        const Pegasus::String& role,
        Pegasus::ObjectPathResponseHandler& handler);

    virtual void enableIndications(
        Pegasus::IndicationResponseHandler & handler);

    virtual void disableIndications();

    virtual void createSubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames,
        const Pegasus::CIMPropertyList & propertyList,
        const Pegasus::Uint16 repeatNotificationPolicy);

    virtual void modifySubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames,
        const Pegasus::CIMPropertyList & propertyList,
        const Pegasus::Uint16 repeatNotificationPolicy);

    virtual void deleteSubscription(
        const Pegasus::OperationContext & context,
        const Pegasus::CIMObjectPath & subscriptionName,
        const Pegasus::Array<Pegasus::CIMObjectPath> & classNames);

    const Meta_Class* find_meta_class(
        const Pegasus::CIMObjectPath& objectPath) const;

    const Meta_Class* find_model_meta_class(
        const Pegasus::CIMObjectPath& objectPath) const;

public:

    Array<String> source_name_spaces;
    Mutex mutex;

private:

    Pegasus::CIMOMHandle* _handle;
    Provider_Handle* _provider;
    Pegasus::IndicationResponseHandler* _handler;
    Atomic_Counter _handler_refs;
    const Meta_Class* _mc;
    Pegasus::CIMOMHandle* _cimom_handle;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Pegasus_Adapter_h */

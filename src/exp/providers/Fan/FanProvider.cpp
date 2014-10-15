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

#include <Pegasus/Common/Config.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>
#include "FanProvider.h"

FanProvider::FanProvider()
{
}

FanProvider::~FanProvider()
{
}

void FanProvider::initialize(CIMOMHandle&)
{
    CIMInstance inst1("Fan");
    inst1.addProperty(CIMProperty("DeviceID", "FAN01"));
    inst1.addProperty(CIMProperty("Speed", Uint64(1000)));
    inst1.addProperty(CIMProperty("DesiredSpeed", Uint64(1000)));
    _instances.append(inst1);

    CIMInstance inst2("Fan");
    inst2.addProperty(CIMProperty("DeviceID", "FAN02"));
    inst2.addProperty(CIMProperty("Speed", Uint64(2000)));
    inst2.addProperty(CIMProperty("DesiredSpeed", Uint64(2000)));
    _instances.append(inst2);

    CIMInstance inst3("Fan");
    inst3.addProperty(CIMProperty("DeviceID", "FAN03"));
    inst3.addProperty(CIMProperty("Speed", Uint64(3000)));
    inst3.addProperty(CIMProperty("DesiredSpeed", Uint64(3000)));
    _instances.append(inst3);
}

void FanProvider::terminate()
{
    delete this;
}

void FanProvider::getInstance(
    const OperationContext& context,
    const CIMObjectPath& instanceReference,
    const Boolean includeQualifiers,
    const Boolean includeClassOrigin,
    const CIMPropertyList& propertyList,
    InstanceResponseHandler& handler)
{
    handler.processing();

    CIMObjectPath objectPath(instanceReference);
    objectPath.setHost(String());
    objectPath.setNameSpace(CIMNamespaceName());

    for (Uint32 i = 0, n = _instances.size(); i < n; i++)
    {
        if (objectPath == _instances[i].getPath())
        {
            try
            {
                handler.deliver(_instances[i]);
            }
            catch(CIMException&)
            {
		// Ignore exception!
            }

            break;
        }
    }

    handler.complete();
}

void FanProvider::enumerateInstances(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const Boolean includeQualifiers,
    const Boolean includeClassOrigin,
    const CIMPropertyList& propertyList,
    InstanceResponseHandler& handler)
{
    handler.processing();

    for (Uint32 i = 0, n = _instances.size(); i < n; i++)
    {
        try
        {
            handler.deliver(_instances[i]);
        }
        catch (CIMException&)
        {
            // Ignore exception!
        }
    }

    handler.complete();
}

void FanProvider::enumerateInstanceNames(
    const OperationContext& context,
    const CIMObjectPath& classReference,
    ObjectPathResponseHandler& handler)
{
    handler.processing();

    for (Uint32 i = 0, n = _instances.size(); i < n; i++)
    {
        try
        {
            handler.deliver(_instances[i].getPath());
        }
        catch(CIMException&)
        {
            // Ignore exception!
        }
    }

    handler.complete();
}

void FanProvider::modifyInstance(
    const OperationContext& context,
    const CIMObjectPath& instanceReference,
    const CIMInstance& instanceObject,
    const Boolean includeQualifiers,
    const CIMPropertyList& propertyList,
    ResponseHandler& handler)
{
    throw CIMException(CIM_ERR_NOT_SUPPORTED);
}

void FanProvider::createInstance(
    const OperationContext& context,
    const CIMObjectPath& instanceReference,
    const CIMInstance& instanceObject,
    ObjectPathResponseHandler& handler)
{
    throw CIMException(CIM_ERR_NOT_SUPPORTED);
}

void FanProvider::deleteInstance(
    const OperationContext& context,
    const CIMObjectPath& instanceReference,
    ResponseHandler& handler)
{
    throw CIMException(CIM_ERR_NOT_SUPPORTED);
}

void FanProvider::invokeMethod(
    const OperationContext& context,
    const CIMObjectPath& objectPath,
    const CIMName& methodName,
    const Array<CIMParamValue>& inParams,
    MethodResultResponseHandler& handler)
{
    if (!objectPath.getClassName().equal("Fan"))
        throw CIMNotSupportedException(objectPath.getClassName().getString());

    handler.processing();

    if (methodName.equal("SetSpeed"))
    {
	// Find the instance:

	CIMInstance instance;

	for (Uint32 i = 0, n = _instances.size(); i < n; i++)
	{
	    if (objectPath == _instances[i].getPath())
	    {
		instance = _instances[i];
		break;
	    }
	}

	if (instance.isUninitialized())
            throw CIMOperationFailedException("no such instance");

	// Extract value for DesiredSpeed parameter:

	if (inParams.size() != 1)
            throw CIMOperationFailedException("too many arguments");

	const CIMParamValue& param = inParams[0];

	if (!String::equalNoCase(param.getParameterName(), "DesiredSpeed"))
            throw CIMOperationFailedException("no such parameter");

	Uint64 desiredSpeed;

	try
	{
	    param.getValue().get(desiredSpeed);
	}
	catch(CIMException&)
	{
            throw CIMOperationFailedException("parameter type mismatch");
	}

	// Set instance.DesiredSpeed from parameter.
	
	Uint32 pos = instance.findProperty("DesiredSpeed");

	if (pos == PEG_NOT_FOUND)
            throw CIMOperationFailedException("missing DesiredSpeed property");

	CIMProperty prop = instance.getProperty(pos);

	if (prop.getValue().getType() != CIMTYPE_UINT64)
            throw CIMOperationFailedException("type mismatch");

	prop.setValue(desiredSpeed);

	// Return Speed

	pos = instance.findProperty("Speed");

	if (pos == PEG_NOT_FOUND)
            throw CIMOperationFailedException("missing DesiredSpeed property");

	prop = instance.getProperty(pos);
	Uint64 speed;

	try
	{
	    prop.getValue().get(speed);
	}
	catch (CIMException&)
	{
            throw CIMOperationFailedException("type mismatch");
	}

	handler.deliver(CIMValue(speed));
    }
    else
    {
        throw CIMNotSupportedException(methodName.getString());
    }

    handler.complete();
}

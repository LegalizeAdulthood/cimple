
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

    if (methodName.equal("add"))
    {
	// Check argument count:

	if (inParams.size() != 2)
            throw CIMOperationFailedException("wrong # arguments");

	// Get x parameter:

	CIMParamValue xParam;

	if (String::equalNoCase(inParams[0].getParameterName(), "x"))
	    xParam = inParams[0];
	else if (String::equalNoCase(inParams[1].getParameterName(), "x"))
	    xParam = inParams[1];

	if (xParam.getValue().getType() != CIMTYPE_UINT32)
            throw CIMOperationFailedException("bad type for parameter x");

	Uint32 x;
	xParam.getValue().get(x);

	// Get y parameter:

	CIMParamValue yParam;

	if (String::equalNoCase(inParams[0].getParameterName(), "y"))
	    yParam = inParams[0];
	else if (String::equalNoCase(inParams[1].getParameterName(), "y"))
	    yParam = inParams[1];

	if (yParam.getValue().getType() != CIMTYPE_UINT32)
            throw CIMOperationFailedException("bad type for parameter x");

	Uint32 y;
	yParam.getValue().get(y);

	// Deliver the sum:

	handler.deliver(CIMValue(x + y));
    }
    else
    {
        throw CIMNotSupportedException(methodName.getString());
    }

    handler.complete();
}

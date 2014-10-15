
static SCODE _makeGadget(
    IWbemServices* name_space, 
    LPWSTR key, 
    long value, 
    IWbemClassObject** newInstance,
    WCHAR* className,
    IWbemContext* context)
{
    SCODE sc;
    VARIANT v;

    // Allocate a new instance:

    IWbemClassObject* classObject = NULL;

    sc = name_space->GetObject(className, 0, context, &classObject, NULL);

    if (sc != S_OK)
        return WBEM_E_FAILED;

    sc = classObject->SpawnInstance(0, newInstance);

    classObject->Release();

    if (FAILED(sc))
        return sc;

    // Set the key property value.

    v.vt = VT_BSTR;
    v.bstrVal = SysAllocString(key);

    if (!v.bstrVal)
        return WBEM_E_OUT_OF_MEMORY;

    sc = (*newInstance)->Put(L"MyKey", 0, &v, 0);
    VariantClear(&v);

    if (FAILED(sc))
        return sc;

    // Set the number property value.

    v.vt = VT_I4;
    v.lVal = value;

    sc = (*newInstance)->Put(L"MyValue", 0, &v, 0);

    if (FAILED(sc))
        return sc;

    return S_OK;
}

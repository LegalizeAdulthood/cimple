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

#include "WMI_Converter.h"
#include "WMI_Containers.h"
#include "utils.h"
#include "BString.h"

CIMPLE_NAMESPACE_BEGIN

Instance* WMI_Converter::to_cimple_instance(
    const Meta_Class* mc,
    IWbemClassObject* inst)
{
    if (!inst)
        return 0;

    WMI_Instance_Container cont(mc->meta_repository, inst);

    Instance* ci = 0;

    if (cont.convert(mc, 0, ci) != 0 || !ci)
    {
        return 0;
    }

    return ci;
}

IWbemClassObject* WMI_Converter::to_wmi_instance(
    IWbemServices* services,
    IWbemContext* context,
    const Instance* inst)
{
    SCODE sc;

    // Check for null parameters (context may be null)

    if (!services || !inst)
        return 0;

    // Get class object from namespace:

    IWbemClassObject* co = 0;
    BString cn(inst->meta_class->name);

    sc = services->GetObject(cn.rep(), 0, context, &co, 0);

    if (sc != S_OK)
    {
        return 0;
    }

    // Create WMI instance:

    IWbemClassObject* wi = 0;
    sc = co->SpawnInstance(0, &wi);

    if (FAILED(sc))
    {
        co->Release();
        return 0;
    }

    // Convert to CIMPLE instance:

    WMI_Instance_Container cont(inst->meta_class->meta_repository, wi);

    if (cont.convert(inst, 0) != 0)
    {
        co->Release();
        wi->Release();
        return 0;
    }

    co->Release();
    return wi;
}

CIMPLE_NAMESPACE_END

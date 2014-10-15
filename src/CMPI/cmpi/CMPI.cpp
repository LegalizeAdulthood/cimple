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

#include "Adapter.h"
#include "CMPI.h"

void __init_mi(
    void** adapter_,
    const CMPIBroker* broker,
    const CMPIContext* context,
    const char* provider_name,
    void* provider_proc,
    MI_Type mi_type,
    void* mi_)
{
    Adapter*& adapter = *((Adapter**)adapter_);

    if (adapter)
        adapter->load_count++;
    else
        adapter = new Adapter(
	    broker, context, provider_name, (Provider_Proc)provider_proc);

    switch (mi_type)
    {
	case MI_TYPE_Instance:
	{
	    CMPIInstanceMI mi= {((void*)adapter), &adapter->instance_ft};
	    memcpy(mi_, &mi, sizeof(mi));
	    break;
	}

	case MI_TYPE_Method:
	{
	    CMPIMethodMI mi= {((void*)adapter), &adapter->method_ft};
	    memcpy(mi_, &mi, sizeof(mi));
	    break;
	}

	case MI_TYPE_Association:
	{
	    CMPIAssociationMI mi = {((void*)adapter), &adapter->association_ft};
	    memcpy(mi_, &mi, sizeof(mi));
	    break;
	}

	case MI_TYPE_Indication:
	{
	    CMPIIndicationMI mi = {((void*)adapter), &adapter->indication_ft};
	    memcpy(mi_, &mi, sizeof(mi));
	    break;
	}
    }
}

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

#ifndef _cmpi_CMPI_h
#define _cmpi_CMPI_h

#include <cimple/config.h>
#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"
#include "linkage.h"

#define __CIMPLE_CMPI_PROVIDER(TYPE,PROVIDER) \
    extern "C" CMPI##TYPE##MI* PROVIDER##_Create_##TYPE##MI( \
	const CMPIBroker* broker, \
	const CMPIContext* context, \
	CMPIStatus*) \
    { \
	static CMPI##TYPE##MI mi; \
	__init_mi( \
	    &__adapter##PROVIDER, \
	    &_cimple_registration_##PROVIDER, \
	    broker, \
	    context, \
	    #PROVIDER, \
	    MI_TYPE_##TYPE, \
	    &mi); \
	return &mi; \
    }

#define CIMPLE_CMPI_INSTANCE_PROVIDER(PROVIDER)  \
    static void* __adapter##PROVIDER = 0; \
    __CIMPLE_CMPI_PROVIDER(Instance, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER(Method, PROVIDER)

#define CIMPLE_CMPI_ASSOCIATION_PROVIDER(PROVIDER)  \
    static void* __adapter##PROVIDER = 0; \
    __CIMPLE_CMPI_PROVIDER(Instance, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER(Method, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER(Association, PROVIDER)

#define CIMPLE_CMPI_INDICATION_PROVIDER(PROVIDER)  \
    static void* __adapter##PROVIDER = 0; \
    __CIMPLE_CMPI_PROVIDER(Method, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER(Indication, PROVIDER)

enum MI_Type
{
    MI_TYPE_Instance,
    MI_TYPE_Method,
    MI_TYPE_Indication,
    MI_TYPE_Association,
};

CIMPLECMPI_LINKAGE void __init_mi(
    void** adapter,
    const void* registration,
    const CMPIBroker* broker,
    const CMPIContext* context,
    const char* provider_name,
    MI_Type mi_type,
    void* mi);

#endif /* _cmpi_CMPI_h */

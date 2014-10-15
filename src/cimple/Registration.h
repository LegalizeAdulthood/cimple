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

#ifndef _cimple_Registration_h
#define _cimple_Registration_h

#include "Provider.h"

#define CIMPLE_MODULE(MODULE) \
    static cimple::Registration* _cimple_registration_head = 0; \
    static const char* _cimple_module_name = #MODULE; \
    extern "C" CIMPLE_EXPORT cimple::Registration* cimple_module() \
	{ return _cimple_registration_head; }

#define CIMPLE_PROVIDER(PROVIDER) \
    static cimple::Registration _cimple_registration_##PROVIDER( \
	_cimple_module_name, \
	#PROVIDER, \
	cimple::PROVIDER::proc, \
	&cimple::PROVIDER::Class::static_meta_class, \
	_cimple_registration_head);

//==============================================================================
//
// Pegasus provider entry point macro.
//
//==============================================================================

#define CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT \
    extern "C" int cimple_pegasus_adapter( \
        void* arg0, void* arg1, void* arg2, void* arg3, \
        void* arg4, void* arg5, void* arg6, void* arg7); \
    extern "C" CIMPLE_EXPORT void* PegasusCreateProvider(void* arg) \
    { \
	void* adapter = 0; \
	cimple_pegasus_adapter( \
	    (void*)'P', arg, _cimple_registration_head, &adapter, 0, 0, 0, 0); \
	return adapter; \
    }

//==============================================================================
//
// CMPI provider entry point macros.
//
//==============================================================================

#define __CIMPLE_CMPI_PROVIDER(TYPE,TYPE_NAME,PROVIDER) \
    extern "C" int cimple_cmpi_adapter( \
        void* arg0, void* arg1, void* arg2, void* arg3, \
        void* arg4, void* arg5, void* arg6, void* arg7); \
    extern "C" CIMPLE_EXPORT void* PROVIDER##_Create_##TYPE_NAME##MI( \
	void* cmpi_broker, \
	void* cmpi_context, \
	void* cmpi_status) \
    { \
	void* _mi = 0; \
	cimple_cmpi_adapter( \
	    (void*)'C', \
	    (void*)&_adapter##PROVIDER, \
	    (void*)&_cimple_registration_##PROVIDER, \
	    (void*)cmpi_broker, \
	    (void*)cmpi_context, \
	    (void*)#PROVIDER, \
	    (void*)TYPE, \
	    (void*)&_mi); \
	return _mi; \
    }

#define CIMPLE_CMPI_INSTANCE_PROVIDER(PROVIDER)  \
    static void* _adapter##PROVIDER = 0; \
    __CIMPLE_CMPI_PROVIDER('I', Instance, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('M', Method, PROVIDER)

#define CIMPLE_CMPI_ASSOCIATION_PROVIDER(PROVIDER)  \
    static void* _adapter##PROVIDER = 0; \
    __CIMPLE_CMPI_PROVIDER('I', Instance, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('M', Method, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('A', Association, PROVIDER)

#define CIMPLE_CMPI_INDICATION_PROVIDER(PROVIDER)  \
    static void* _adapter##PROVIDER = 0; \
    __CIMPLE_CMPI_PROVIDER('M', Method, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('N', Indication, PROVIDER)

//==============================================================================
//
// CIMPLE_CLASS_DEPENDENCY()
//
//==============================================================================

#define CIMPLE_CLASS_DEPENDENCY(CLASS) \
    const char* __class_##CLASS = "@(#)CLASS_DEPENDENCY=" #CLASS;

//==============================================================================
//
// CIMPLE adapter entry point (all CIMPLE adapters implement this interface).
// The only pre-defined operation is 'T', which returns the provider type
// which (so far) is one of the following:
//
//     'P' - Pegasus C++ Provider
//     'C' - CMPI Provider
//
//==============================================================================

CIMPLE_NAMESPACE_BEGIN

struct CIMPLE_CIMPLE_LINKAGE Registration
{
    const char* module_name;
    const char* provider_name;
    Provider_Proc provider_proc;
    const Meta_Class* meta_class;
    Registration* next;

    Registration(
	const char* module_name_,
	const char* provider_name_, 
	Provider_Proc provider_proc_,
	const Meta_Class* meta_class_,
	Registration*& next_);
};

inline Registration::Registration(
    const char* module_name_,
    const char* provider_name_, 
    Provider_Proc provider_proc_,
    const Meta_Class* meta_class_,
    Registration*& next_)
{
    provider_name = provider_name_;
    module_name = module_name_;
    provider_proc = provider_proc_;
    meta_class = meta_class_;
    next = next_;

    // Prepend to registration list:
    next_ = this;
}

typedef Registration* (*Module_Proc)();

CIMPLE_NAMESPACE_END

#endif /* _cimple_Registration_h */

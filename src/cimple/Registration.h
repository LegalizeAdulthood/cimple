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

#define CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT \
    extern "C" extern void* __cimple_create_pegasus_adapter(void*, void*); \
    extern "C" void* PegasusCreateProvider(void* arg) \
    { \
	return __cimple_create_pegasus_adapter( \
	    arg, _cimple_registration_head); \
    } \

CIMPLE_NAMESPACE_BEGIN

struct CIMPLE_LIBCIMPLE_LINKAGE Registration
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

typedef Registration* (*Module_Proc)();

CIMPLE_NAMESPACE_END

#endif /* _cimple_Registration_h */

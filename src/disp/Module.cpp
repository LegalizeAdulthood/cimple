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

#include <dlfcn.h>
#include "Module.h"
#include <cimple/Error.h>
#include "Envelope.h"

CIMPLE_NAMESPACE_BEGIN

typedef Registration* (*Module_Proc)();

Module::Module(void* handle, Module_Proc proc) : 
    _handle(handle), _providers_loaded(false)
{
    _registration = proc();
}

Module::~Module()
{
    if (_providers_loaded)
	unload_providers();

    dlclose(_handle);
}

void Module::load_providers()
{
    if (_providers_loaded)
	return;

    // ATTN: call cimple_module_load() here!

    // Load all providers in this module:

    for (Registration* p = _registration; p; p = p->next)
    {
	Envelope* env = new Envelope(p);
	env->load();
	_envelopes.append(env);
    }

    // Mark as providers_loaded:

    _providers_loaded = true;
}

void Module::unload_providers()
{
    if (!_providers_loaded)
	return;

    // ATTN: call cimple_module_unload() here!

    // Unload the providers first:

    for (List_Elem* p = _envelopes.head; p; p = p->next)
    {
	Envelope* env = (Envelope*)p;
	env->unload();
	delete env;
    }

    // Clear the list:

    _envelopes.clear();

    // Mark as unproviders_loaded:

    _providers_loaded = false;
}

Envelope* Module::find_provider(const char* class_name)
{
    for (List_Elem* p = _envelopes.head; p; p = p->next)
    {
	Envelope* env = (Envelope*)p;

	if (strcasecmp(env->class_name(), class_name) == 0)
	    return env;
    }

    // Not found:
    return 0;
}

CIMPLE_NAMESPACE_END

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

#include <cimple/flags.h>
#include <cimple/Strings.h>
#include <dirent.h>
#include <dlfcn.h>
#include "Cache.h"
#include "string.h"
#include <cimple/Error.h>

// ATTN: implement destroy() method.

CIMPLE_NAMESPACE_BEGIN

Cache::Cache() : _last_meta_class(0)
{
}

Cache::~Cache()
{
    for (size_t i = 0; i < _modules.size(); i++)
	delete _modules[i];
}

static bool _is_lib_name(const String& name)
{
    // Return true if name is the name of a library.

#ifdef CIMPLE_WINDOWS
    return name.is_suffix(".dll", 4);
#else
    return name.is_prefix("lib", 3) && name.is_suffix(".so", 3);
#endif
}

Cache* Cache::create(const char* lib_dir)
{
    Error::clear();

    // Create cache

    Cache* cache = new Cache();

    // Scan the directory for files of the form: lib<prefix><name>.so.

    DIR* dir = opendir(lib_dir);

    if (!dir)
	return 0;

    // ATTN: readdir not thread safe!

    for (dirent* ent; (ent = readdir(dir)) != NULL; )
    {
	String name(ent->d_name);

	if (name == "." || name == "..")
	    continue;

	// Ignore non-libraries:

	if (!_is_lib_name(name.c_str()))
	    continue;

	// Load the library.

	String path(lib_dir, "/", name.c_str());

	void* handle = dlopen(path.c_str(), RTLD_NOW | RTLD_GLOBAL);

	if (!handle)
	{
	    CIMPLE_ERROR((
		"failed to load : \"%s\": %s", path.c_str(), dlerror()));

	    closedir(dir);
	    delete cache;
	    return 0;
	}

	// Load cimple_module() entry point:

	Module_Proc module_proc = (Module_Proc)dlsym(handle, "cimple_module");

	if (module_proc)
	{
	    if (cache->_add_module(handle, module_proc) != 0)
	    {
		delete cache;
		closedir(dir);
		return 0;
	    }
	    continue;
	}

	dlclose(handle);
    }

    // Close directory:

    closedir(dir);

    return cache;
}

Envelope* Cache::get_provider_by_class(const char* class_name)
{
    for (size_t i = 0; i < _envelopes.size(); i++)
    {
	Envelope* env = (Envelope*)_envelopes[i];

	if (eqi(env->class_name(), class_name))
	    return env;
    }

    // Not found:
    return 0;
}

Envelope* Cache::get_provider_by_name(const char* provider_name)
{
    for (size_t i = 0; i < _envelopes.size(); i++)
    {
	Envelope* env = (Envelope*)_envelopes[i];

	if (eqi(env->provider_name(), provider_name))
	    return env;
    }

    // Not found:
    return 0;
}

const Meta_Class* Cache::get_meta_class(const char* class_name) const
{
    if (_last_meta_class && eqi(_last_meta_class->name, class_name))
	return _last_meta_class;

    for (size_t i = 0; i < _modules.size(); i++)
    {
	const Meta_Class* mc = _modules[i]->registration()->meta_class;

	if (eqi(class_name, mc->name))
	    return mc;

	if (mc->meta_repository)
	{
	    mc = find_meta_class(mc->meta_repository, class_name);

	    if (mc)
	    {
		((Cache*)this)->_last_meta_class = mc;
		return mc;
	    }
	}
    }

    // Not found!
    return 0;
}

const Meta_Repository* Cache::get_meta_repository()
{
    // ATTN: solve problem of multiple meta repositories! For the moment,
    // we take the first meta repository we find assuming that there will
    // never be more than one.

    for (size_t i = 0; i < _modules.size(); i++)
    {
	const Meta_Class* mc = _modules[i]->registration()->meta_class;

	if (mc->meta_repository)
	    return mc->meta_repository;
    }

    // Not found!
    return 0;
}

int Cache::_add_module(void* handle, Module_Proc module_proc)
{
    Module* module = new Module(handle, module_proc);

    // Load providers:

    module->load_providers();

    // Add to _envelopes and _meta_classes arrays:

    for (List_Elem* p = module->envelopes(); p; p = p->next)
    {
	Envelope* env = (Envelope*)p;
	const Meta_Class* mc = env->meta_class();

	// Check for duplicate providers:

	for (size_t i = 0; i < _envelopes.size(); i++)
	{
	    const Meta_Class* tmp = _envelopes[i]->meta_class();

	    if (eqi(mc->name, tmp->name))
	    {
		CIMPLE_ERROR(("more than one provider for class %s", mc->name));
		delete module;
		return -1;
	    }
	}

	_envelopes.append(env);
    }

    // Add module to the list:

    _modules.append(module);
    return 0;
}

CIMPLE_NAMESPACE_END

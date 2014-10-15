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

#include <cimple/flags.h>
#include <cimple/Strings.h>
#include <dirent.h>
#include <dlfcn.h>
#include "Cache.h"
#include "string.h"
#include "Error.h"

// ATTN: implement destroy() method.

CIMPLE_NAMESPACE_BEGIN

Cache::Cache()
{
}

Cache::~Cache()
{
    for (size_t i = 0; i < _modules.size(); i++)
	delete _modules[i];

    for (size_t i = 0; i < _repositories.size(); i++)
	delete _repositories[i];
}

Cache* Cache::create(const char* lib_dir, const char* prefix)
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

	// Ignore modules without the "cmpl" prefix.

#ifdef CIMPLE_WINDOWS
	String full_prefix = prefix;
	String suffix = ".dll";
#else
	String full_prefix = "lib";
	full_prefix.append(prefix);
	String suffix = ".so";
#endif

	if (!name.is_prefix(full_prefix.c_str(), full_prefix.size()))
	    continue;

	if (!name.is_suffix(suffix.c_str(), suffix.size()))
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

	// Load cimple_repository() entry point (since it was not a module).

	Repository_Proc repository_proc = 
	    (Repository_Proc)dlsym(handle, "cimple_repository");

	if (repository_proc)
	{
	    if (cache->_add_repository(handle, repository_proc) != 0)
	    {
		delete cache;
		closedir(dir);
		return 0;
	    }
	    continue;
	}

	// It was neither a module nor a repository:

	CIMPLE_ERROR(("%s is neither a module nor a directory", path.c_str()));
	closedir(dir);
	delete cache;
	return 0;

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

	if (strcasecmp(env->class_name(), class_name) == 0)
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

	if (strcasecmp(env->provider_name(), provider_name) == 0)
	    return env;
    }

    // Not found:
    return 0;
}

const Meta_Class* Cache::get_meta_class(const char* class_name) const
{
    for (size_t i = 0; i < _meta_classes.size(); i++)
    {
	const Meta_Class* mc = _meta_classes[i];

	if (strcasecmp(class_name, mc->name) == 0)
	    return mc;
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

	    if (strcasecmp(mc->name, tmp->name) == 0)
	    {
		CIMPLE_ERROR(("more than one provider for class %s", mc->name));
		delete module;
		return -1;
	    }
	}

	// Add class to list:

	if (_add_meta_class(mc) != 0)
	{
	    delete module;
	    return -1;
	}

	_meta_classes.append(mc);
	_envelopes.append(env);
    }

    // Add module to the list:

    _modules.append(module);
    return 0;
}

int Cache::_add_repository(void* handle, Repository_Proc repository_proc)
{
    Repository* repository = new Repository(handle, repository_proc);

    // Add all the classes in this repository to the master list:

    const Meta_Class* const* meta_classes = repository->meta_classes();
    size_t num_meta_classes = repository->num_meta_classes();

    for (size_t i = 0; i < num_meta_classes; i++)
    {
	if (_add_meta_class(meta_classes[i]) == -1)
	{
	    delete repository;
	    return -1;
	}
    }

    // Add repository to the list:

    _repositories.append(repository);
    return 0;
}

int Cache::_add_meta_class(const Meta_Class* meta_class)
{
    // See if it conflicts with an existing class:

    for (size_t i = 0; i < _meta_classes.size(); i++)
    {
	const Meta_Class* mc = _meta_classes[i];

	if (strcasecmp(mc->name, meta_class->name) == 0)
	{
	    if (mc->crc == meta_class->crc)
		return 0;

	    CIMPLE_ERROR(("conflicting CRC on class %s", mc->name));
	    return -1;
	}
    }

    // Add the class to the array:

    _meta_classes.append(meta_class);

    return 0;
}

CIMPLE_NAMESPACE_END

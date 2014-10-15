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

#ifndef _cimple_Cache_h
#define _cimple_Cache_h

#include <cimple/Raw_Array.h>
#include "Envelope.h"
#include "Module.h"
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

/** This object caches modules (from module libraries). Each module library 
    has an entry point called cimple_module().
*/
class CIMPLEDISP_LINKAGE Cache
{
public:

    /** Creates a new cache by scanning the given directory for modules
	and repositories. This causes every library to be loaded (whether 
	it has a cimple_module() or not).
	@param path directory containing the providers or repositories.
	@return pointer to a new cache or null on error.
    */
    static Cache* create(const char* path);

    /** Find a provider with the given class name.
    */
    Envelope* get_provider_by_class(const char* class_name);

    /** Find a provider with the given provider name.
    */
    Envelope* get_provider_by_name(const char* provider_name);

    /** Get meta class.
    */
    const Meta_Class* get_meta_class(const char* class_name) const;

    /** Get meta repository.
    */
    const Meta_Repository* get_meta_repository();

    /** Get number of modules in cache.
    */
    size_t num_modules() const;

    /** Get number of providers.
    */
    size_t num_providers() const;

    /** Get the i-th provider. */
    Envelope* get_provider(size_t i);

    void dump() const;

private:

    Cache();

    ~Cache();

    int _add_module(void* handle, Module_Proc module_proc);
    int _add_meta_class(const Meta_Class* meta_class);

    Raw_Array<Module*> _modules;
    Raw_Array<Envelope*> _envelopes;
    const Meta_Class* _last_meta_class;
};

inline size_t Cache::num_modules() const
{
    return _modules.size();
}

inline size_t Cache::num_providers() const
{
    return _envelopes.size();
}

inline Envelope* Cache::get_provider(size_t i)
{
    return _envelopes[i];
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Cache_h */

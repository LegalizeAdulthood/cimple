/*

Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
// Generated by genprov 1.2.4
#ifndef _StringArrayClass_Provider_h
#define _StringArrayClass_Provider_h

#include <cimple/cimple.h>
#include "StringArrayClass.h"

CIMPLE_NAMESPACE_BEGIN

class StringArrayClass_Provider
{
public:

    typedef StringArrayClass Class;

    StringArrayClass_Provider();

    ~StringArrayClass_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const StringArrayClass* model,
        StringArrayClass*& instance);

    Enum_Instances_Status enum_instances(
        const StringArrayClass* model,
        Enum_Instances_Handler<StringArrayClass>* handler);

    Create_Instance_Status create_instance(
        StringArrayClass* instance);

    Delete_Instance_Status delete_instance(
        const StringArrayClass* instance);

    Modify_Instance_Status modify_instance(
        const StringArrayClass* model,
        const StringArrayClass* instance);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _StringArrayClass_Provider_h */

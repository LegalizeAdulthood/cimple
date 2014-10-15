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
/**
 * Encode and decode (pack and unpack) instances into binary form.
 */

#ifndef _cimple_Instance_Enc_h
#define _cimple_Instance_Enc_h

#include "config.h"
#include "Meta_Class.h"
#include "Array.h"
#include "Atomic.h"
#include "Buffer.h"

CIMPLE_CIMPLE_LINKAGE
void pack_instance(Buffer& out, const Instance* inst, bool keys_only = false);

CIMPLE_CIMPLE_LINKAGE
void pack_instance_local(Buffer& out, const Instance* inst);

CIMPLE_CIMPLE_LINKAGE
Instance* unpack_instance(
    const Buffer& in, 
    size_t& pos, 
    const Meta_Class* (*lookup)(const char* class_name, void* client_data),
    void* client_data);

CIMPLE_CIMPLE_LINKAGE
Instance* unpack_instance_local(
    const Buffer& in, 
    size_t& pos, 
    const Meta_Class* (*lookup)(const char* class_name, void* client_data),
    void* client_data);

CIMPLE_NAMESPACE_END


#endif /* _cimple_Instance_Enc_h */

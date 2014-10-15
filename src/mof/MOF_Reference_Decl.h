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

#ifndef _MOF_Reference_Decl_h
#define _MOF_Reference_Decl_h

#include "MOF_Config.h"
#include "MOF_Feature.h"
#include "MOF_Object_Reference.h"

class MOF_LINKAGE MOF_Reference_Decl : public MOF_Feature
{
public:

    MOF_Reference_Decl();

    virtual void print() const;

    virtual void validate();

    virtual MOF_Element* clone() const;

    void validate_obj_ref(MOF_Object_Reference* obj_ref);

    char* class_name;
    class MOF_Class_Decl* class_decl;
    char* alias;
    MOF_Object_Reference* obj_ref;
};

#endif /* _MOF_Reference_Decl_h */

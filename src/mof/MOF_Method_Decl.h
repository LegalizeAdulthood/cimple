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

/*
    Define a method.  Adds data_type and parameter list (pointer to parameters)
    to MOF_Feature.
*/
#ifndef _MOF_Method_Decl_h
#define _MOF_Method_Decl_h

#include "MOF_Config.h"
#include "MOF_Parameter.h"
#include "MOF_Feature.h"

class MOF_LINKAGE MOF_Method_Decl : public MOF_Feature
{
public:

    MOF_Method_Decl();

    virtual void print() const;

    virtual void validate();

    virtual MOF_Element* clone() const;

    virtual void set_owning_class(const char* owning_class);

    static void check_compatibility(
        const char* class_name,
        const MOF_Method_Decl* m1,
        const MOF_Method_Decl* m2);

    // Data type for the method
    int data_type;
    // pointer to the MOF_Parameters
    MOF_Parameter* parameters;
};

#endif /* _MOF_Method_Decl_h */

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
    Adds feature type (Property, Reference, Method) to Qualified Element
*/
#ifndef _MOF_Feature_h
#define _MOF_Feature_h

#include "MOF_Config.h"
#include "MOF_Qualifier.h"
#include "MOF_Qualifier_Info.h"
#include "MOF_Qualified_Element.h"

#define MOF_FEATURE_PROP 1
#define MOF_FEATURE_REF 2
#define MOF_FEATURE_METHOD 3

class MOF_LINKAGE MOF_Feature : public MOF_Qualified_Element
{
public:

    MOF_Feature() : type(0) { }

    virtual void print() const = 0;

    virtual void validate() = 0;

    virtual MOF_Element* clone() const = 0;

    int type;
};

#endif /* _MOF_Feature_h */

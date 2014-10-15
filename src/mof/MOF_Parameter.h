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
    Specialization for method parameters. Since this is a subclass of
    Qualified Element, it includes the ability to handle parameter qualifiers.
*/
#ifndef _MOF_Parameter_h
#define _MOF_Parameter_h

#include "MOF_Config.h"
#include "MOF_Qualified_Element.h"
#include "MOF_Qualifier.h"
#include "MOF_Qualifier_Info.h"

class MOF_LINKAGE MOF_Parameter : public MOF_Qualified_Element
{
public:

    MOF_Parameter() : data_type(0), ref_name(0) { }

    virtual MOF_Element* clone() const;

    /** Return zero if the two parameters are compatible or negative one if not.
    */
    static int compatible(
        const char* class_name,
        const char* method_name,
        MOF_Parameter* p1,
        MOF_Parameter* p2);

    /** Check for parameters with duplicate name in this list.
    */
    void check_duplicates() const;

    int data_type;
    int array_index;
    char* ref_name;
};

#endif /*_MOF_Parameter_h */

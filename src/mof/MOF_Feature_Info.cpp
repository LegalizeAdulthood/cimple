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

#include "MOF_Feature.h"
#include "MOF_Feature_Info.h"
#include "MOF_Class_Decl.h"

MOF_Feature_Info::MOF_Feature_Info() 
    : feature(0), class_origin(0), propagated(false)
{

}

MOF_Feature_Info::~MOF_Feature_Info()
{
    /* Nothing to do */
}

MOF_Element* MOF_Feature_Info::clone() const
{
    MOF_ASSERT("not implemented" == 0);
    return 0;
}

void MOF_Feature_Info::print_list() const
{
    const MOF_Feature_Info* p;

    for (p = this; p; p = (MOF_Feature_Info*)p->next)
    {
        printf("  + %s origin=%s propagated=%d\n", 
            p->feature->name, 
            p->class_origin->name, 
            p->propagated);
    }

    printf("\n");
}

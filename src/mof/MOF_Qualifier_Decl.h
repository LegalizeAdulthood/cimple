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

#ifndef MOF_Qualifier_Decl_h
#define MOF_Qualifier_Decl_h

#include "MOF_Config.h"
#include "MOF_Literal.h"
#include "MOF_Flavor.h"
#include "MOF_Named_Element.h"

#define MOF_SCOPE_SCHEMA 1
#define MOF_SCOPE_CLASS 2
#define MOF_SCOPE_ASSOCIATION 4
#define MOF_SCOPE_INDICATION 8
#define MOF_SCOPE_PROPERTY 16
#define MOF_SCOPE_REFERENCE 32
#define MOF_SCOPE_METHOD 64
#define MOF_SCOPE_PARAMETER 128
#define MOF_SCOPE_ANY \
    (MOF_SCOPE_SCHEMA | \
    MOF_SCOPE_CLASS | \
    MOF_SCOPE_ASSOCIATION | \
    MOF_SCOPE_INDICATION | \
    MOF_SCOPE_PROPERTY | \
    MOF_SCOPE_REFERENCE | \
    MOF_SCOPE_METHOD | \
    MOF_SCOPE_PARAMETER)

#define MOF_QT_ABSTRACT (1 << 0)
#define MOF_QT_AGGREGATE (1 << 1)
#define MOF_QT_AGGREGATION (1 << 2)
#define MOF_QT_ASSOCIATION (1 << 3)
#define MOF_QT_COUNTER (1 << 4)
#define MOF_QT_DELETE (1 << 5)
#define MOF_QT_DN (1 << 6)
#define MOF_QT_EMBEDDEDOBJECT (1 << 7)
#define MOF_QT_EXPENSIVE (1 << 8)
#define MOF_QT_EXPERIMENTAL (1 << 9)
#define MOF_QT_GAUGE (1 << 10)
#define MOF_QT_IFDELETED (1 << 11)
#define MOF_QT_IN (1 << 12)
#define MOF_QT_INDICATION (1 << 13)
#define MOF_QT_INVISIBLE (1 << 14)
#define MOF_QT_KEY (1 << 15)
#define MOF_QT_LARGE (1 << 16)
#define MOF_QT_OCTETSTRING (1 << 17)
#define MOF_QT_OUT (1 << 18)
#define MOF_QT_READ (1 << 19)
#define MOF_QT_REQUIRED (1 << 20)
#define MOF_QT_STATIC (1 << 21)
#define MOF_QT_TERMINAL (1 << 22)
#define MOF_QT_WEAK (1 << 23)
#define MOF_QT_WRITE (1 << 24)

class MOF_LINKAGE MOF_Qualifier_Decl : public MOF_Named_Element
{
public:

    MOF_Qualifier_Decl();

    ~MOF_Qualifier_Decl();

    virtual MOF_Element* clone() const;

    void validate();

    static void handle(MOF_Qualifier_Decl* qual_decl);

    void print() const;

    static void print_static_list();

    static MOF_Qualifier_Decl* find(char* name);

    static MOF_Qualifier_Decl* list;

    int data_type;
    int array_index;
    MOF_Literal* initializer;
    MOF_mask scope;
    MOF_mask flavor;
};

#endif /* MOF_Qualifier_Decl_h */

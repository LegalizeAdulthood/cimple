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

#ifndef _MOF_Flavor_h
#define _MOF_Flavor_h

#include "MOF_Config.h"

#define MOF_FLAVOR_ENABLEOVERRIDE 1
#define MOF_FLAVOR_DISABLEOVERRIDE 2
#define MOF_FLAVOR_RESTRICTED 4
#define MOF_FLAVOR_TOSUBCLASS 8
#define MOF_FLAVOR_TRANSLATABLE 16
#define MOF_FLAVOR_DEFAULTS (MOF_FLAVOR_ENABLEOVERRIDE | MOF_FLAVOR_TOSUBCLASS)

class MOF_LINKAGE MOF_Flavor
{
public:

    static MOF_mask merge(MOF_mask to, MOF_mask from);

    static void print(MOF_mask flavor);

    static MOF_mask fixup(MOF_mask flavor, bool provide_defaults);
};

#endif /* _MOF_Flavor_h */

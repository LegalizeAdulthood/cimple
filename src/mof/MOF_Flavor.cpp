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

#include "MOF_Flavor.h"
#include "MOF_Error.h"

MOF_mask MOF_Flavor::merge(
    MOF_mask to, 
    MOF_mask from)
{
    MOF_mask mask = to;

    /*
     * If ENABLEOVERRIDE or DISABLEOVERRIDE not already set, then inherit it.
     */

    if (!(mask & (MOF_FLAVOR_ENABLEOVERRIDE | MOF_FLAVOR_DISABLEOVERRIDE)))
        mask |= from & (MOF_FLAVOR_ENABLEOVERRIDE | MOF_FLAVOR_DISABLEOVERRIDE);

    /*
     * If TOSUBCLASS or RESTRICTED not already set, then inherit it.
     */

    if (!(mask & (MOF_FLAVOR_TOSUBCLASS | MOF_FLAVOR_RESTRICTED)))
        mask |= from & (MOF_FLAVOR_TOSUBCLASS | MOF_FLAVOR_RESTRICTED);

    /* 
     * If TRANSLATABLE not already set, inherit it:
     */

    if (!(mask & MOF_FLAVOR_TRANSLATABLE))
        mask |= from & MOF_FLAVOR_TRANSLATABLE;

    return mask;
}

void MOF_Flavor::print(
    MOF_mask flavor)
{
    printf("flavor(");

    if (flavor & MOF_FLAVOR_ENABLEOVERRIDE)
        printf(" EnableOverride");

    if (flavor & MOF_FLAVOR_DISABLEOVERRIDE)
        printf(" DisableOverride");

    if (flavor & MOF_FLAVOR_TOSUBCLASS)
        printf(" ToSubclass");

    if (flavor & MOF_FLAVOR_RESTRICTED)
        printf(" Restricted");

    if (flavor & MOF_FLAVOR_TRANSLATABLE)
        printf(" Translatable");

    printf(" )\n");
}

MOF_mask MOF_Flavor::fixup(
    MOF_mask flavor,
    bool provide_defaults)
{
    MOF_mask tmp = 0;
    
    /*
     * Check for conflicting flavors:
     */

    if ((flavor & MOF_FLAVOR_ENABLEOVERRIDE) &&
        (flavor & MOF_FLAVOR_DISABLEOVERRIDE))
        MOF_error("conflicting flavors: ENABLEOVERRIDE and DISABLEOVERRIDE");

    if ((flavor & MOF_FLAVOR_TOSUBCLASS) &&
        (flavor & MOF_FLAVOR_RESTRICTED))
        MOF_error("conflicting flavors: TOSUBCLASS and RESTRICTED");

    /*
     * Set the flavors:
     */

    tmp = flavor;

    /*
     * Set defaults for omitted flavors:
     */

    if (provide_defaults)
    {
        if (!(tmp & (MOF_FLAVOR_DISABLEOVERRIDE | MOF_FLAVOR_ENABLEOVERRIDE)))
            tmp |= MOF_FLAVOR_ENABLEOVERRIDE;

        if (!(tmp & (MOF_FLAVOR_TOSUBCLASS | MOF_FLAVOR_RESTRICTED)))
            tmp |= MOF_FLAVOR_TOSUBCLASS;
    }

    return tmp;
}

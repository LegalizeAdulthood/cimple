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

#include "Meta_Property.h"
#include "Type.h"
#include "Meta_Feature.h"
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

bool property_eq(
    const Meta_Property* mp, 
    const void* value1,
    const void* value2)
{
    if (null_of(mp, value1) != null_of(mp, value2))
	return false;

    if (mp->subscript == 0)
    {
	switch (mp->type)
	{
	    case BOOLEAN:
		return *((boolean*)value1) == *((boolean*)value2);

	    case UINT8:
	    case SINT8:
		return *((uint8*)value1) == *((uint8*)value2);

	    case UINT16:
	    case SINT16:
	    case CHAR16:
		return *((uint16*)value1) == *((uint16*)value2);

	    case UINT32:
	    case SINT32:
		return *((uint32*)value1) == *((uint32*)value2);

	    case UINT64:
	    case SINT64:
		return *((uint64*)value1) == *((uint64*)value2);

	    case REAL32:
		return *((real32*)value1) == *((real32*)value2);

	    case REAL64:
		return *((real64*)value1) == *((real64*)value2);

	    case STRING:
		return *((String*)value1) == *((String*)value2);

	    case DATETIME:
		return *((Datetime*)value1) == *((Datetime*)value2);
	}
    }
    else
    {
	switch (mp->type)
	{
	    case BOOLEAN:
		return *((Array_boolean*)value1) == *((Array_boolean*)value2);

	    case UINT8:
	    case SINT8:
		return *((Array_uint8*)value1) == *((Array_uint8*)value2);

	    case UINT16:
	    case SINT16:
	    case CHAR16:
		return *((Array_uint16*)value1) == *((Array_uint16*)value2);

	    case UINT32:
	    case SINT32:
		return *((Array_uint32*)value1) == *((Array_uint32*)value2);

	    case UINT64:
	    case SINT64:
		return *((Array_uint64*)value1) == *((Array_uint64*)value2);

	    case REAL32:
		return *((Array_real32*)value1) == *((Array_real32*)value2);

	    case REAL64:
		return *((Array_real64*)value1) == *((Array_real64*)value2);

	    case STRING:
		return *((Array_String*)value1) == *((Array_String*)value2);

	    case DATETIME:
		return *((Array_Datetime*)value1) == *((Array_Datetime*)value2);
	}
    }

    // Unreachable!
    return true;
}

CIMPLE_NAMESPACE_END

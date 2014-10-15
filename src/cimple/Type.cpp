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

#include "Type.h"
#include "Array.h"
#include <cctype>

CIMPLE_NAMESPACE_BEGIN

size_t const type_size[] =
{
    sizeof(boolean),
    sizeof(uint8),
    sizeof(sint8),
    sizeof(uint16),
    sizeof(sint16),
    sizeof(uint32),
    sizeof(sint32),
    sizeof(uint64),
    sizeof(sint64),
    sizeof(real32),
    sizeof(real64),
    sizeof(char16),
    sizeof(String),
    sizeof(Datetime),
};

size_t const literal_type_size[] =
{
    sizeof(boolean),
    sizeof(uint8),
    sizeof(sint8),
    sizeof(uint16),
    sizeof(sint16),
    sizeof(uint32),
    sizeof(sint32),
    sizeof(uint64),
    sizeof(sint64),
    sizeof(real32),
    sizeof(real64),
    sizeof(char16),
    sizeof(char*), /* STRING */
    sizeof(char*), /* DATETIME */
};

const char* const type_name[] =
{
    "boolean",
    "uint8",
    "sint8",
    "uint16",
    "sint16",
    "uint32",
    "sint32",
    "uint64",
    "sint64",
    "real32",
    "real64",
    "char16",
    "string",
    "datetime",
};

void fprint_string(FILE* os, const char* str)
{
    fprintf(os, "\"");

    while (*str)
    {
        char c = *str++;

        switch (c)
        {
            case '\n':
                fprintf(os, "\\n");
                break;

            case '\r':
                fprintf(os, "\\r");
                break;

            case '\t':
                fprintf(os, "\\t");
                break;

            case '\f':
                fprintf(os, "\\f");
                break;

            case '"':
                fprintf(os, "\\\"");
                break;

            default:
                fprintf(os, "%c", c);
        }
    }

    fprintf(os, "\"");
}

void print_string(const char* str)
{
    fprint_string(stdout, str);
}

void fprint_scalar(FILE* os, Type type, const void* value)
{
    switch (type)
    {
        case BOOLEAN:
        {
            fprintf(os, "%s", *((boolean*)value) ? "true" : "false");
            break;
        }

        case UINT8:
        {
            fprintf(os, "%u", *((uint8*)value));
            break;
        }

        case SINT8:
        {
            fprintf(os, "%d", *((sint8*)value));
            break;
        }

        case UINT16:
        {
            fprintf(os, "%u", *((uint16*)value));
            break;
        }

        case SINT16:
        {
            fprintf(os, "%d", *((sint16*)value));
            break;
        }

        case UINT32:
        {
            fprintf(os, "%u", *((uint32*)value));
            break;
        }

        case SINT32:
        {
            fprintf(os, "%d", *((sint32*)value));
            break;
        }

        case UINT64:
        {
            fprintf(os, CIMPLE_LLU, *((uint64*)value));
            break;
        }

        case SINT64:
        {
            fprintf(os, CIMPLE_LLD, *((sint64*)value));
            break;
        }

        case REAL32:
        {
            fprintf(os, "%f", *((real32*)value));
            break;
        }

        case REAL64:
        {
            fprintf(os, "%f", *((real64*)value));
            break;
        }

        case CHAR16:
        {
            fprintf(os, "%u", ((char16*)value)->code());
            break;
        }

        case STRING:
        {
            fprint_string(os, *((const char* const*)value));
            break;
        }

        case DATETIME:
        {
            fprintf(os, "%s", *((const char* const*)value));
            break;
        }
    }
}

void print_scalar(Type type, const void* value)
{
    fprint_scalar(stdout, type, value);
}

void fprint_array(
    FILE* os, 
    Type type, 
    const void* elements_, 
    size_t num_elements)
{
    const char* elements = (const char*)elements_;
    bool first = true;

    for (size_t i = 0; i < num_elements; i++)
    {
        if (first)
            first = false;
        else
            fprintf(os, ", ");

        fprint_scalar(os, type, elements);
        elements += literal_type_size[type];
    }
}

void print_array(Type type, const void* elements_, size_t num_elements)
{
    fprint_array(stdout, type, elements_, num_elements);
}

int type_name_to_type(const char* name, Type& type)
{
    size_t n = strlen(name);

    if (n == 0)
        return -1;

    char c1 = tolower(name[0]);
    char c2 = tolower(name[n-1]);
    size_t code = n ^ c1 ^ c2;

    switch(code)
    {
        case 9:
            if (strcasecmp(name, "datetime") == 0)
            {
                type = DATETIME;
                return 0;
            }
            break;
        case 11:
            if (strcasecmp(name, "boolean") == 0)
            {
                type = BOOLEAN;
                return 0;
            }
            break;
        case 18:
            if (strcasecmp(name, "string") == 0)
            {
                type = STRING;
                return 0;
            }
            break;
        case 64:
            if (strcasecmp(name, "real64") == 0)
            {
                type = REAL64;
                return 0;
            }
            break;
        case 65:
            if (c1 == 'u' && strcasecmp(name, "uint32") == 0)
            {
                type = UINT32;
                return 0;
            }
            if (c1 == 's' && strcasecmp(name, "sint64") == 0)
            {
                type = SINT64;
                return 0;
            }
            break;
        case 67:
            if (strcasecmp(name, "sint16") == 0)
            {
                type = SINT16;
                return 0;
            }
            break;
        case 69:
            if (strcasecmp(name, "uint16") == 0)
            {
                type = UINT16;
                return 0;
            }
            break;
        case 70:
            if (strcasecmp(name, "real32") == 0)
            {
                type = REAL32;
                return 0;
            }
            break;
        case 71:
            if (c1 == 's' && strcasecmp(name, "sint32") == 0)
            {
                type = SINT32;
                return 0;
            }
            if (c1 == 'u' && strcasecmp(name, "uint64") == 0)
            {
                type = UINT64;
                return 0;
            }
            break;
        case 72:
            if (strcasecmp(name, "uint8") == 0)
            {
                type = UINT8;
                return 0;
            }
            break;
        case 78:
            if (strcasecmp(name, "sint8") == 0)
            {
                type = SINT8;
                return 0;
            }
            break;
        case 83:
            if (strcasecmp(name, "char16") == 0)
            {
                type = CHAR16;
                return 0;
            }
            break;
    }

    // Failed!
    return -1;
}

CIMPLE_NAMESPACE_END

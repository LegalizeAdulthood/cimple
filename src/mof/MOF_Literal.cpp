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

#include "MOF_Literal.h"
#include "MOF_Yacc.h"
#include "MOF_Error.h"
#include "MOF_String.h"

MOF_Literal::~MOF_Literal()
{
    MOF_ASSERT(this != 0);

    if (value_type == TOK_STRING_VALUE)
        free(string_value);
}

static bool _test_value(
    int data_type,
    MOF_Literal* literal)
{
    switch (literal->value_type)
    {
        case TOK_INT_VALUE:
        {
            MOF_sint64 int_value = literal->int_value;

            switch (data_type)
            {
                case TOK_UINT8: 
                    return int_value == ((MOF_uint8)int_value);

                case TOK_SINT8: 
                    return int_value == ((MOF_sint8)int_value);

                case TOK_UINT16: 
                    return int_value == ((MOF_uint16)int_value);

                case TOK_SINT16: 
                    return int_value == ((MOF_sint16)int_value);

                case TOK_UINT32: 
                    return int_value == ((MOF_uint32)int_value);

                case TOK_SINT32: 
                    return int_value == ((MOF_sint32)int_value);

                case TOK_UINT64: 
                    return 
                        (MOF_uint64)int_value == ((MOF_uint64)int_value);

                case TOK_SINT64: 
                    return int_value == ((MOF_sint64)int_value);

                default:
                    return false;
            }
        }

        case TOK_REAL_VALUE:
        {
            switch (data_type)
            {
                case TOK_REAL32: 
                    return true;

                case TOK_REAL64: 
                    return true;

                default:
                    return false;
            }
        }

        case TOK_CHAR_VALUE:
            return data_type == TOK_CHAR16;

        case TOK_BOOL_VALUE:
            return data_type == TOK_BOOLEAN;

        case TOK_STRING_VALUE:
        {
            switch (data_type)
            {
                case TOK_STRING: 
                    return true;

                case TOK_DATETIME: 
                    return true;

                default:
                    return false;
            }
        }

        case TOK_NULL_VALUE:
            return true;

        default:
            return false;
    }

    return false;
}

void MOF_Literal::validate(
    const char* object_type,
    const char* object_name,
    int data_type,
    int array_index)
{
    MOF_ASSERT(this != 0);

    int size;
    MOF_Literal* p;

    /*
     * Validate the cardinality of the type.
     */

    size = list_size();
    MOF_ASSERT(size != 0);

    if (array_index == -1)
    {
        /* VLA */
    }
    else if (array_index == 0)
    {
        /* Scalar */

        if (size != 1)
        {
            MOF_error_printf("multiple initializers for %s: \"%s\"",
                object_type, object_name);
        }
    }
    else
    {
        /* FLA */

        if (size > array_index)
        {
            MOF_error_printf("too many initializers for %s: \"%s\"",
                object_type, object_name);
        }
        else if (size < array_index)
        {
            MOF_error_printf("too few initializers for %s: \"%s\"",
                object_type, object_name);
        }
    }

    /*
     * Test each of the literals to see if they can really be converted
     * to the given argument type.
     */

    for (p = this; p; p = (MOF_Literal*)p->next)
    {
        if (!_test_value(data_type, p))
        {
            MOF_error_printf("invalid initializer for %s: \"%s\"",
                object_type, object_name);
        }
    }
}

bool MOF_Literal::identical(
    MOF_Literal* lit1,
    MOF_Literal* lit2)
{
    MOF_Literal* p1;
    MOF_Literal* p2;

    /*
     * Check if either is NULL:
     */

    if (lit1 == 0 && lit2 == 0)
        return true;

    if (lit1 == 0)
        return false;

    if (lit2 == 0)
        return false;

    /*
     * Verify that list sizes are the same:
     */

    if (lit1->list_size() != lit2->list_size())
        return false;

    /*
     * Verify that value types are the same:
     */

    if (lit1->value_type != lit2->value_type)
        return false;

    /*
     * Verify that each literal value is the same:
     */

    p1 = lit1;
    p2 = lit2;

    while (p1 && p2)
    {
        MOF_ASSERT(p1->value_type == p2->value_type);
        MOF_ASSERT(lit1->value_type == p1->value_type);
        MOF_ASSERT(lit2->value_type == p2->value_type);

        switch (p1->value_type)
        {
            case TOK_INT_VALUE:
            {
                if (p1->int_value != p2->int_value)
                    return false;
                break;
            }

            case TOK_REAL_VALUE:
            {
                if (p1->real_value != p2->real_value)
                    return false;
                break;
            }

            case TOK_CHAR_VALUE:
            {
                if (p1->char_value != p2->char_value)
                    return false;
                break;
            }

            case TOK_BOOL_VALUE:
            {
                if (p1->bool_value != p2->bool_value)
                    return false;
                break;
            }

            case TOK_STRING_VALUE:
            {
                if (p1->string_value == 0 && p2->string_value == 0)
                    break;

                if (p1->string_value == 0)
                    return false;

                if (p2->string_value == 0)
                    return false;

                if (strcmp(p1->string_value, p2->string_value) != 0)
                    return false;

                break;
            }

            case TOK_NULL_VALUE:
            {
                /* Nothing to do! */
                break;
            }

            default:
                MOF_ASSERT(false);
                return false;
        }

        p1 = (MOF_Literal*)p1->next;
        p2 = (MOF_Literal*)p2->next;
    }

    return true;
}

static void _print_char(
    FILE* stream,
    char ch)
{
    fprintf(stream, "'");

    switch (ch)
    {
        case '\b': 
            fprintf(stream, "\b");
            break;

        case '\t': 
            fprintf(stream, "\\t");
            break;

        case '\n': 
            fprintf(stream, "\\n");
            break;

        case '\f': 
            fprintf(stream, "\\f");
            break;

        case '\r': 
            fprintf(stream, "\\r");
            break;

        case '\"': 
            fprintf(stream, "\\\"");
            break;

        case '\'': 
            fprintf(stream, "\\'");
            break;

        case '\\': 
            fprintf(stream, "\\");
            break;

        default:
        {
            /* ATTN: handle other non-printable characters */
            fprintf(stream, "%c", ch);
        }
    }

    fprintf(stream, "'");
}

static void _print_string(
    FILE* stream,
    const char* asc7)
{
    fprintf(stream, "\"");

    char* p = MOF_escape(asc7);
    MOF_ASSERT(p != 0);

    fprintf(stream, "%s", p);
    fprintf(stream, "\"");

    free(p);
}

static void _print(
    FILE* stream,
    const MOF_Literal* literal)
{
    if (!literal)
    {
        fprintf(stream, "NULL");
        return;
    }

    switch (literal->value_type)
    {
        case TOK_INT_VALUE:
        {
            fprintf(stream, "%lld", literal->int_value);
            break;
        }

        case TOK_REAL_VALUE:
        {
            fprintf(stream, "%E", literal->real_value);
            break;
        }

        case TOK_CHAR_VALUE:
        {
            // ATTN: this only print single byte chars:
            _print_char(stream, (char)literal->char_value);
            break;
        }

        case TOK_BOOL_VALUE:
        {
            if (literal->bool_value)
                fprintf(stream, "true");
            else
                fprintf(stream, "false");

            break;
        }

        case TOK_STRING_VALUE:
            _print_string(stream, literal->string_value);
            break;

        case TOK_NULL_VALUE:
        {
            fprintf(stream, "NULL");
            break;
        }

        default:
            MOF_ASSERT(false);
    }
}

void MOF_Literal::print(
    FILE* stream,
    bool is_array) const
{
    if (is_array)
    {
        const MOF_Literal* p;

        fprintf(stream, "{");

        for (p = this; p; p = (MOF_Literal*)p->next)
        {
            _print(stream, p);

            if (p->next != 0)
                fprintf(stream, ",");
        }

        fprintf(stream, "}");
    }
    else
        _print(stream, this);
}

MOF_Element* MOF_Literal::clone() const
{
    MOF_Literal* tmp = new MOF_Literal();

    tmp->value_type = value_type;

    if (value_type == TOK_STRING_VALUE)
        tmp->string_value = strdup(string_value);
    else
        tmp->int_value = int_value;

    return tmp;
}

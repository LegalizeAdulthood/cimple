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

#include "MOF_Lex_Utils.h"
#include "MOF_String.h"
#include "MOF_Buffer.h"

int MOF_read_string(
    MOF_input_proc input_proc,
    MOF_error_proc error_proc,
    char** raw,
    char** escaped)
{
    if (raw)
        *raw = 0;

    if (escaped)
        *escaped = 0;

    /*
     * Process characters until a closing quote is encountered.
     */

    MOF_Buffer buf;
    int ch;

    while (((ch = (*input_proc)()) != -1) && ch != '"')
    {
        int next_char = '\0';

        buf.append(ch);

        if (ch == '\\')
        {
            if ((next_char = (*input_proc)()) == -1)
            {
                (*error_proc)("out of input");
                return -1;
            }

            buf.append(next_char);
        }
    }

    if (ch == -1)
    {
        (*error_proc)("unterminated string literal");
        return -1;
    }

    buf.append('\0');

    /*
     * Now unescape special characters:
     */

    char* asc7 = MOF_unescape(buf.data());

    if (asc7 == 0)
    {
        (*error_proc)("bad string literal");
        return -1;
    }

    if (raw)
        *raw = buf.steal_data();

    if (escaped)
        *escaped = asc7;
    else
        free(asc7);

    return 0;
}

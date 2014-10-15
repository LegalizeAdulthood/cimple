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

#include <cassert>
#include <disp/DZT_String.h>

using namespace cimple;

int main(int argc, char** argv)
{
    DZT_String str;

    str.append("Monday");
    str.append("Tuesday");
    str.append("Wednesday");
    str.append("Thursday");
    str.append("Friday");
    str.append("Saturday");
    str.append("Sunday");

    size_t i = 0;

    for (const char* p = str.str(); p; dzt_next(p), i++)
    {
	switch (i)
	{
	    case 0:
		assert(strcmp(p, "Monday") == 0);
		break;
	    case 1:
		assert(strcmp(p, "Tuesday") == 0);
		break;
	    case 2:
		assert(strcmp(p, "Wednesday") == 0);
		break;
	    case 3:
		assert(strcmp(p, "Thursday") == 0);
		break;
	    case 4:
		assert(strcmp(p, "Friday") == 0);
		break;
	    case 5:
		assert(strcmp(p, "Saturday") == 0);
		break;
	    case 6:
		assert(strcmp(p, "Sunday") == 0);
		break;
	    default:
		assert(0);
		break;
	}

	// printf("[%s]\n", p);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

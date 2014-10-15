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
#include "AAA2.h"
#include "CCC.h"
#include "DDD.h"

using namespace cimple;

int main(int argc, char** argv)
{
#if 0
    AAA2* aaa2 = AAA2::create();

    random_initialize(aaa2);

    aaa2->left = CCC::create();
    random_initialize(aaa2->left);

    aaa2->right = DDD::create();
    random_initialize(aaa2->right);

    // print(aaa2);

    AAA2::destroy(aaa2);

    printf("+++++ passed all tests (%s)\n", argv[0]);
#endif
    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test6/main.cpp,v 1.4 2007/03/07 20:25:30 mbrasher-public Exp $");

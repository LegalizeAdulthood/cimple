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
/*
    Test of the serialization and persistence functions including
    pack_instance
    unpack_instance
    The Enc functions
    
*/

//#include "Link.h"
#include <cimple/cimple.h>
#include <cassert>
#include <cstdio>
#include "All_Properties.h"


using namespace cimple;

int main(int argc, char** argv)
{
    {
        All_Properties* all = All_Properties::create(true);
        all->__name_space = "xyz";
        all->booleanScalar.set(true);
        print(all);
        //fprint(stderr, all);
        Buffer b;
        pack_instance(b, all);
        Buffer b1;
        All_Properties* rtn;
        unpack_instance(b1,0, &All_Properties::static_meta_class,);
     }

    printf("+++++ passed all tests (%s)\n", argv[0]);
    return 0;
}


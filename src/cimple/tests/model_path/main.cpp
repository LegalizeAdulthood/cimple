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
#include <cimple/cimple.h>
#include "Part.h"
#include "Glue.h"

using namespace cimple;

int main(int argc, char** argv)
{
    // Create Glue object.

    Ref<Glue> glue1(Glue::create());
    nullify_non_keys(glue1.ptr());

    Ref<Part> part1(Part::create());
    nullify_non_keys(part1.ptr());
    part1->key1.value = true;
    part1->key2.value = 9999;
    part1->key3.value = "Seriously?";

    glue1->left = part1->clone();
    glue1->right = part1->clone();

    // print(glue1);

    // Create a Part instance name from an instance path.
    {
        const char PATH[] = 
            "Part.key1=true,key2=9999,key3=\"Seriously?\"";

        Ref<Instance> part2 =
            model_path_to_instance(&Part::static_meta_class, PATH);
        assert(part2 != 0);
        // print(part2, true);

        assert(identical(part1.ptr(), part2.ptr()));
    }

    // Create a Glue instance name from an instance path.
    {
        // Convert CIM model path to an instance.

        const char PATH[] = "Glue."
            "left=\"Part.key1=true,key2=9999,key3=\\\"Seriously?\\\"\","
            "right=\"Part.key1=true,key2=9999,key3=\\\"Seriously?\\\"\"";

        Ref<Instance> glue2 =
            model_path_to_instance(&Glue::static_meta_class, PATH);
        assert(glue2 != 0);

        Ref<Instance> tmp(glue2);
        Ref<Instance> tmp2(glue2);
        Ref<Glue> glue3(glue2.ptr());

#if 0
        print(glue1.ptr());
        print(glue2.ptr());
        print(glue3.ptr());
#endif

        assert(identical(glue2.ptr(), glue1.ptr()));
        assert(identical(glue2.ptr(), glue3.ptr()));
        assert(identical(glue1.ptr(), glue3.ptr()));

        // Convert the instance back to a CIM model path:

        String path;

        int result = instance_to_model_path(glue2.ptr(), path);
        assert(result == 0);

        assert(path == PATH);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}


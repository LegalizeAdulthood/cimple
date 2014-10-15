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
#include <cctype>
#include <cimple/Meta_Class.h>
#include <cimple/Enc.h>
#include "Everything.h"
#include "CIM_ComputerSystem.h"

using namespace cimple;

static Everything* _create_instance()
{
    Everything* inst1 = Everything::create();
    inst1->a.value = true;
    inst1->b.value = 8;
    inst1->c.value = 16;
    inst1->d.value = 32;
    inst1->e.value = 64;
    inst1->f.value = 32.0;
    inst1->g.value = 64.0;
    inst1->h.value = 'A';
    inst1->i.value = "Hello";
    inst1->j.value = Datetime::now();
    inst1->k.null = true;
    inst1->l.null = true;
    inst1->m.null = true;
    inst1->kk.null = true;
    inst1->ll.null = true;
    inst1->mm.null = true;
    return inst1;
}

void test(const Meta_Class* mc)
{
    assert(identical(mc, mc));

    Buffer buffer;
    pack_meta_class(buffer, mc);

    size_t pos = 0;
    Meta_Class* meta_class = unpack_meta_class(buffer, pos);
    assert(meta_class != 0);

    assert(identical(meta_class, mc));
    assert(identical(meta_class, meta_class));

    //print(meta_class);

    destroy(meta_class);
}

int main(int argc, char** argv)
{
    const struct Meta_Repository* meta_repository = 
	CIM_ComputerSystem::static_meta_class.meta_repository;
    assert(meta_repository != 0);

    for (size_t i = 0; i < meta_repository->num_meta_classes; i++)
    {
	const Meta_Class* mc = meta_repository->meta_classes[i];

	if (strcasecmp(mc->name,  "Foo") == 0)
	    test(mc);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

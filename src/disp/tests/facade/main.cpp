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
#include <disp/Facade.h>
#include "Thing.h"
#include "Assoc.h"

using namespace cimple;

int main(int argc, char** argv)
{
#ifdef CIMPLE_USE_FACADE
    {
	Thing* thing = Thing::create();
	Facade f(thing);

	f.set_boolean("w", true, false);
	f.set_uint32("x", 99, false);
	f.set_string("y", String("Hello World"), false);
	Array<uint32> z;
	z.append(111);
	z.append(222);
	z.append(333);
	f.set_uint32_array("z", z, false);

	assert(thing->w.value == true);
	assert(thing->x.value == 99);
	assert(thing->y.value == "Hello World");
	assert(thing->z.value == z);
	// f.print();

	Instance* inst = thing;

	Thing* thing2 = cast<Thing*>(inst);

	assert(thing2 != 0);
	assert((void*)thing2 == (void*)inst);
    }

    {
	Thing* left = Thing::create();
	left->key.value = 1000;

	Thing* right = Thing::create();
	right->key.value = 2000;

	Assoc* assoc = Assoc::create();
	Facade a(assoc);

	a.set_ref("left", left);
	// a.set_ref("right", right);

	// a.print();
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

#endif /* CIMPLE_USE_FACADE */
    return 0;
}

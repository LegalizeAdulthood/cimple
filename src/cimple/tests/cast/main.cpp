/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include <cimple/cimple.h>
#include <cassert>
#include "D.h"
#include "E.h"

using namespace cimple;

int main(int argc, char** argv)
{
    {
	A* a = A::create();
	B* b = B::create();
	C* c = C::create();
	D* d = D::create();

	Instance* ia = a;
	Instance* ib = b;
	Instance* ic = c;
	Instance* id = d;

	assert(is_a<A>(id));
	assert(is_a<B>(id));
	assert(is_a<C>(id));
	assert(is_a<D>(id));

	assert(is_a<A>(ic));
	assert(is_a<B>(ic));
	assert(is_a<C>(ic));
	assert(!is_a<D>(ic));

	assert(is_a<A>(ib));
	assert(is_a<B>(ib));
	assert(!is_a<C>(ib));
	assert(!is_a<D>(ib));

	assert(is_a<A>(ia));
	assert(!is_a<B>(ia));
	assert(!is_a<C>(ia));
	assert(!is_a<D>(ia));

	assert(cast<A*>(id) == (A*)d);
	assert(cast<B*>(id) == (B*)d);
	assert(cast<C*>(id) == (C*)d);
	assert(cast<D*>(id) == (D*)d);

	assert(cast<A*>(ic) == (A*)c);
	assert(cast<B*>(ic) == (B*)c);
	assert(cast<C*>(ic) == (C*)c);
	assert(cast<D*>(ic) == (D*)0);

	assert(cast<A*>(ib) == (A*)b);
	assert(cast<B*>(ib) == (B*)b);
	assert(cast<C*>(ib) == 0);
	assert(cast<D*>(ib) == 0);

	assert(cast<A*>(ia) == a);
	assert(cast<B*>(ia) == 0);
	assert(cast<C*>(ia) == 0);
	assert(cast<D*>(ia) == 0);
    }

    // Test down casting:
    {
	const A* a = A::create();
	const B* b = B::create();
	const C* c = C::create();
	const D* d = D::create();

	const Instance* ia = a;
	const Instance* ib = b;
	const Instance* ic = c;
	const Instance* id = d;

	assert(is_a<A>(id));
	assert(is_a<B>(id));
	assert(is_a<C>(id));
	assert(is_a<D>(id));

	assert(is_a<A>(ic));
	assert(is_a<B>(ic));
	assert(is_a<C>(ic));
	assert(!is_a<D>(ic));

	assert(is_a<A>(ib));
	assert(is_a<B>(ib));
	assert(!is_a<C>(ib));
	assert(!is_a<D>(ib));

	assert(is_a<A>(ia));
	assert(!is_a<B>(ia));
	assert(!is_a<C>(ia));
	assert(!is_a<D>(ia));

	const D* td = cast<const D*>(id);
	assert(td != 0);

	assert(cast<const A*>(id) == (A*)d);
	assert(cast<const B*>(id) == (B*)d);
	assert(cast<const C*>(id) == (C*)d);
	assert(cast<const D*>(id) == (D*)d);

	assert(cast<const A*>(ic) == (A*)c);
	assert(cast<const B*>(ic) == (B*)c);
	assert(cast<const C*>(ic) == (C*)c);
	assert(cast<const D*>(ic) == (D*)0);

	assert(cast<const A*>(ib) == (A*)b);
	assert(cast<const B*>(ib) == (B*)b);
	assert(cast<const C*>(ib) == (C*)0);
	assert(cast<const D*>(ib) == (D*)0);

	assert(cast<const A*>(ia) == (A*)a);
	assert(cast<const B*>(ia) == 0);
	assert(cast<const C*>(ia) == 0);
	assert(cast<const D*>(ia) == 0);
    }

    // Test up casting:
    {
	A* a = A::create();
	B* b = B::create();
	C* c = C::create();
	D* d = D::create();
	E* e = E::create();

	assert(cast<A*>(d) == (A*)d);
	assert(cast<B*>(d) == (B*)d);
	assert(cast<C*>(d) == (C*)d);
	assert(cast<A*>(e) == 0);

	d->a.value = 100;
	d->b.value = 200;
	d->c.value = 300;
	d->d.value = 400;

	A* pa = cast<A*>(d);
	assert(pa != 0);

	assert(pa->a.value == 100);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

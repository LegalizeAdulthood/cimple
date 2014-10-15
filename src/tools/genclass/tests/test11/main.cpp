#include "X.h"

using namespace cimple;

int main(int argc, char** argv)
{
    {
        X* x = X::create();
        x->a = A::create();
        x->a->key.set(1000);

        X* x2 = x->clone();
        assert(x2->a);
        assert(x2->a->key.value == 1000);

        destroy(x);
        destroy(x2);
    }

    {
        X_foo1_method* m = X_foo1_method::create();
        m->return_value = B::create();
        m->return_value = B::create();

        X_foo1_method* m2 = m->clone();
        assert(m2->return_value);
        m2->return_value->key.value = 1000;
        assert(m2->return_value->key.value == 1000);

        destroy(m);
        destroy(m2);
    }

    {
        X_foo2_method* m = X_foo2_method::create();
        m->c = C::create();
        m->c->key.set(999);

        X_foo2_method* m2 = m->clone();

        assert(m->c);
        assert(m->c->key.value == 999);

        destroy(m);
        destroy(m2);
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

#include <cimple/cimple.h>
#include "Person.h"

using namespace cimple;

int main(int argc, char** argv)
{
    Person* p = Person::create();

    p->Id.value = 444556666;
    p->LastName.value = "Brasher";
    p->MiddleInitial.value = 'E';
    p->FirstName.value = "Michael";
    p->Age.null = true;

    print(p);

    return 0;
}

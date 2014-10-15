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

    Person::destroy(p);

    Person_Ref r;
    Person_Ref r2 = r;

#if 0
    r.set_Id(444556666);
    r.set_LastName("Brasher");
    r.set_MiddleInitial('E');
    r.set_FirstName("Michael");
    r.clear_Age();
    r.print();
#endif

    return 0;
}

#include <cimple/CIM_Class.h>
#include <unistd.h>

using namespace cimple;

void test2()
{
    CIM_Class cc("Thing");
    cc.add_property("Number", UINT32, CIM_Class::KEY);
    cc.add_property("Message", STRING);
    cc.add_property("Flag", BOOLEAN);

    cc.set_property("Number", 99);
    cc.set_property("Message", "Hello world");
    cc.set_property("Flag", true);

    assert(cc.count() == 3);

    for (size_t i = 0; i < cc.count(); i++)
    {
        if (i == 0)
            assert(strcmp(cc.get_name(i), "Number") == 0);
        else if (i == 1)
            assert(strcmp(cc.get_name(i), "Message") == 0);
        else if (i == 2)
            assert(strcmp(cc.get_name(i), "Flag") == 0);

        if (cc.get_type(i) == CIM_Class::STRING)
        {
            String x;
            cc.get_property(i, x);
            assert(x == "Hello world");
            // printf("value[%s]\n", x.c_str());
        }
        else if (cc.get_type(i) == CIM_Class::BOOLEAN)
        {
            boolean x;
            cc.get_property(i, x);
            assert(x == true);
        }
        else if (cc.get_type(i) == CIM_Class::UINT32)
        {
            uint32 x;
            cc.get_property(i, x);
            assert(x == 99);
        }
    }
}

void test1()
{
    CIM_Class cc("Thing");
    cc.add_property("Number", UINT32, CIM_Class::KEY);
    cc.add_property("Message", STRING);
    cc.add_property("Flag", BOOLEAN);
    cc.add_property("Time", DATETIME);
    cc.add_property("Char", CHAR16);
    cc.add_fla_property("Sizes", UINT32, 99);
    cc.add_vla_property("Flags", BOOLEAN);
    cc.add_vla_property("Colors", STRING);
    cc.add_vla_property("Chars", CHAR16);
    cc.add_vla_property("Times", DATETIME);

    // BOOLEAN:
    {
        cc.set_property("Flag", true);

        {
            boolean Flag;
            cc.get_property("Flag", Flag);
            assert(Flag == true);
        }

        cc.set_property("Flag", false);

        {
            boolean Flag;
            cc.get_property("Flag", Flag);
            assert(Flag == false);
        }
    }

    // UINT32:
    {
        cc.set_property("Number", uint8(99));
        uint32 Number;
        cc.get_property("Number", Number);
        assert(Number == 99);
    }

    // CHAR16:
    {
        cc.set_property("Char", char16('A'));
        char16 Char;
        cc.get_property("Char", Char);
        assert(Char == 'A');
    }

    // STRING:
    {
        cc.set_property("Message", "Hello World");
        String Message;
        cc.get_property("Message", Message);
        assert(Message == "Hello World");
    }

    // Datetime:
    {
        Datetime Now = Datetime::now();
        cc.set_property("Time", Now);
        Datetime Time;
        cc.get_property("Time", Time);
        assert(Time == Now);
    }

    // Array<uint32>
    {
        Array<uint32> a;
        a.append(100);
        a.append(200);
        a.append(300);
        cc.set_property("Sizes", a);
    }

    // Array<boolean>
    {
        Array<boolean> a1;
        a1.append(true);
        a1.append(false);
        a1.append(true);
        cc.set_property("Flags", a1);
        Array<boolean> a2;
        cc.get_property("Flags", a2);
        assert(a1 == a2);
    }

    // Array<String>
    {
        Array<String> a1;
        a1.append("Red");
        a1.append("Green");
        a1.append("Blue");
        cc.set_property("Colors", a1);

        Array<String> a2;
        cc.get_property("Colors", a2);
        assert(a1 == a2);
    }

    // Array<char16>
    {
        Array<char16> a1;
        a1.append('X');
        a1.append('Y');
        a1.append('Z');
        cc.set_property("Chars", a1);

        Array<char16> a2;
        cc.get_property("Chars", a2);
        assert(a1 == a2);
    }

    {
        Datetime x0 = Datetime::now();
        sleep(1);
        Datetime x1 = Datetime::now();
        sleep(1);
        Datetime x2 = Datetime::now();

        Array<Datetime> a1;
        a1.append(x0);
        a1.append(x1);
        a1.append(x2);
        cc.set_property("Times", a1);

        Array<Datetime> a2;
        cc.get_property("Times", a2);
        assert(a1 == a2);
    }

    assert(!cc.is_null("Chars"));
    cc.clear("Chars");
    assert(cc.is_null("Chars"));

    // cc.print();
}

int main(int argc, char** argv)
{
    try
    {
        test1();
        test2();
    }
    catch (Exception& e)
    {
        fprintf(stderr, "Exception: %s\n", e.message().c_str());
        exit(1);
    }

    printf("++++ passed all tests (%s)\n", argv[0]);

    return 0;
}

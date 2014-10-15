#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>

PEGASUS_USING_PEGASUS;

// class TheClass
// {
//    string u;
//    uint32 v;
//    boolean w;
//    real32 x;
//    uint32 y[];
//    string z[];
// };

void example()
{
    try
    {
        CIMInstance inst("TheClass");
        inst.addProperty(CIMProperty("u", "hello"));
        inst.addProperty(CIMProperty("v", Uint32(99)));
        inst.addProperty(CIMProperty("w", Boolean(true)));
        inst.addProperty(CIMProperty("x", Real32(1.5)));

        Array<Uint32> y;
        y.append(1);
        y.append(2);
        y.append(3);
        inst.addProperty(CIMProperty("y", y));

        Uint32 pos = inst.findProperty("v");

        CIMProperty prop;

        if (pos != PEG_NOT_FOUND)
        {
            Uint32 v;
            prop = inst.getProperty(pos);
            prop.getValue().get(v);
        }
    }
    catch(...)
    {
    }
}

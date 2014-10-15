#include <cstdlib>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>

using namespace Pegasus;
using namespace std;

int main()
{
    try
    {
        CIMClient cc;
	cc.connect("localhost", 5988, String(), String());

	Array<CIMObjectPath> result = cc.enumerateInstanceNames(
	    "/root/cimv2",
	    "CIM_ManagedElement");

	for (Uint32 i = 0; i < result.size(); i++)
	{
	    cout << result[i].toString() << endl;
	}
    }
    catch (Exception& e)
    {
	cerr << "Exception: " << e.getMessage() << endl;
        exit(1);
    }

    return 0;
}

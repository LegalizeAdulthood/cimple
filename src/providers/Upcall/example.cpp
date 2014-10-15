// example code for testing the creation of a function that
// returns Refs of a CIMPLE class upcall
// See the provider for correct code

typedef Ref<CIM_ComputerSystem> Ref_ComputerSystem;

static int _enum_CIM_ComputerSystem(
    Array<Ref_ComputerSystem>& computer_systems)
{
    // Create the cimple Model for CIM_ComputerSystem

    CIM_ComputerSystem* model = CIM_ComputerSystem::create();

    // Define the instance enumerator

    Instance_Enumerator ie;

    // Call the enumerate function for CIM_ComputerSystem

    if (cimom::enum_instances("root/cimv2", model, ie) != 0)
        return -1;

    // Iterate the enumeration responses

    for (; ie; ie++)
    {
        // Create Instance for the next iterator return
        Ref<Instance> inst = ie();

        // Cast to a CIM_ComputerSystem instance

        Ref_ComputerSystem ccs(inst.ptr());

        if (css.ptr())
            computer_systems.append(ccs);
    }

    return 0;
}

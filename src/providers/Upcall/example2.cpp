// example of discussed extension to the CIMPLE model that would directly
// return instances in the cast class removing the need for the user
// to do the case.  NOTE: This is not in the code today.
// This would be an expansion to the template mechanism
// 
typedef Ref<CIM_ComputerSystem> Ref_ComputerSystem;

static int _enum_CIM_ComputerSystem(Array<Ref_ComputerSystem>& computer_systems)
{
    Instance_Enumerator<CIM_ComputerSystem> ie;

    if (cimom::enum_instances<CIM_ComputerSystem>("root/cimv2", ie) != 0)
        return -1;

    for (; ie; ie++)
    {
        computer_systems.append(ie());
    }

    return 0;
}

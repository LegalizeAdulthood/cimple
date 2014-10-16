#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>

using namespace Pegasus;

static void _inject_object_path(
    CIMInstance& instance,
    const CIMObjectPath& objectPath,
    const char* tag)
{
    Array<CIMKeyBinding> bindings;

    bindings.append(CIMKeyBinding("Tag", tag, CIMKeyBinding::STRING));

    bindings.append(CIMKeyBinding(
        "CreationClassName", "Benchmark2", CIMKeyBinding::STRING));

    instance.setPath(CIMObjectPath(
        objectPath.getHost(),
        objectPath.getNameSpace(),
        "Benchmark2",
        bindings));
}

static CIMInstance _create_Benchmark(
    const CIMObjectPath& objectPath,
    const char* tag)
{
    CIMInstance ci("Benchmark2");

    ci.addProperty(CIMProperty("Caption", String("Caption")));

    ci.addProperty(CIMProperty("Description", String("Description")));

    ci.addProperty(CIMProperty("ElementName", String("ElementName")));

    ci.addProperty(
        CIMProperty("InstallDate", CIMDateTime::getCurrentDateTime()));

    ci.addProperty(CIMProperty("Name", String("Name")));

    Array<Uint16> OperationalStatus;
    OperationalStatus.append(1);
    ci.addProperty(CIMProperty("OperationalStatus", OperationalStatus));

    Array<String> StatusDescriptions;
    StatusDescriptions.append("StatusDescriptions");
    ci.addProperty(CIMProperty("StatusDescriptions", StatusDescriptions));

    ci.addProperty(CIMProperty("Status", String("Status")));

    ci.addProperty(CIMProperty("Tag", String(tag)));

    ci.addProperty(CIMProperty("CreationClassName", String("Benchmark2")));

    ci.addProperty(CIMProperty("Manufacturer", String("Manufacturer")));

    ci.addProperty(CIMProperty("Model", String("Model")));

    ci.addProperty(CIMProperty("SKU", String("SKU")));

    ci.addProperty(CIMProperty("SerialNumber", String("SerialNumber")));

    ci.addProperty(CIMProperty("Version", String("Version")));

    ci.addProperty(CIMProperty("PartNumber", String("PartNumber")));

    ci.addProperty(
        CIMProperty("OtherIdentifyingInfo", String("OtherIdentifyingInfo")));

    ci.addProperty(CIMProperty("PoweredOn", Boolean(true)));

    ci.addProperty(
        CIMProperty("ManufactureDate", CIMDateTime::getCurrentDateTime()));

    ci.addProperty(
        CIMProperty("VendorEquipmentType", String("VendorEquipmentType")));

    ci.addProperty(CIMProperty("UserTracking", String("UserTracking")));

    ci.addProperty(CIMProperty("CanBeFRUed", Boolean(true)));

    ci.addProperty(CIMProperty("RemovalConditions", Uint16(0)));

    ci.addProperty(CIMProperty("Removable", Boolean(true)));

    ci.addProperty(CIMProperty("Replaceable", Boolean(true)));

    ci.addProperty(CIMProperty("HotSwappable", Boolean(true)));

    ci.addProperty(CIMProperty("Height", Real32(1.0)));

    ci.addProperty(CIMProperty("Depth", Real32(1.0)));

    ci.addProperty(CIMProperty("Width", Real32(1.0)));

    ci.addProperty(CIMProperty("Weight", Real32(100.0)));

    ci.addProperty(CIMProperty("HostingBoard", Boolean(true)));

    ci.addProperty(CIMProperty("SlotLayout", String("SlotLayout")));

    ci.addProperty(CIMProperty("RequiresDaughterBoard", Boolean(false)));

    ci.addProperty(CIMProperty("SpecialRequirements", Boolean(false)));

    ci.addProperty(CIMProperty(
        "RequirementsDescription", String("RequirementsDescription")));

    Array<Sint16> OperatingVoltages;
    OperatingVoltages.append(6);
    ci.addProperty(CIMProperty("OperatingVoltages", OperatingVoltages));

    _inject_object_path(ci, objectPath, tag);

    return ci;
}

int main()
{
    CIMObjectPath objectPath;

    for (size_t i = 0; i < 100000; i++)
    {
        CIMInstance inst = _create_Benchmark(objectPath, "Tag");
    }

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Create2/main.cpp,v 1.2 2007/03/07 20:24:10 mbrasher-public Exp $");

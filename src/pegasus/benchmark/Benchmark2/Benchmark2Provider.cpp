#include "Benchmark2Provider.h"

extern size_t memo_deep_size(const void* ptr, size_t size);

#define NUM_INSTANCES 100

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

Benchmark2Provider::Benchmark2Provider()
{
}

Benchmark2Provider::~Benchmark2Provider()
{
}

void Benchmark2Provider::initialize(Pegasus::CIMOMHandle& cimom)
{
}

void Benchmark2Provider::terminate()
{
}

void Benchmark2Provider::getInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::InstanceResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark2Provider::getInstance()");
}

void Benchmark2Provider::enumerateInstances(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::InstanceResponseHandler& handler)
{
    for (size_t i = 0; i < NUM_INSTANCES; i++)
    {
        char buffer[32];
        sprintf(buffer, "Pegasus-%d", int(i));
        CIMInstance inst = _create_Benchmark(objectPath, buffer);

#if 0
        size_t size = memo_deep_size(&inst, sizeof(CIMInstance));
        printf("SIZE[%d]\n", (int)size);
#endif

        inst.filter(includeQualifiers, includeClassOrigin, propertyList);
        handler.deliver(inst);
    }
}

void Benchmark2Provider::enumerateInstanceNames(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    Pegasus::ObjectPathResponseHandler& handler)
{

    
}

void Benchmark2Provider::modifyInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMInstance& instance,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::ResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark2Provider::modifyInstance()");
}

void Benchmark2Provider::createInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMInstance& instance,
    Pegasus::ObjectPathResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark2Provider::createInstance()");
}

void Benchmark2Provider::deleteInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    Pegasus::ResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark2Provider::deleteInstance()");
}

extern "C" PEGASUS_EXPORT 
Pegasus::CIMProvider* PegasusCreateProvider(const Pegasus::String& name)
{
    if (name == "Benchmark2_Provider")
        return new Benchmark2Provider();

    return 0;
}

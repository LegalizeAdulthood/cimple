#include "Benchmark4Provider.h"

extern size_t memo_deep_size(const void* ptr, size_t size);

#define NUM_INSTANCES 100

using namespace Pegasus;

static void _inject_object_path(
    const Pegasus::CIMObjectPath& objectPath,
    CIMInstance& instance, 
    const String& tag)
{
    Array<CIMKeyBinding> bindings;

    bindings.append(CIMKeyBinding("Tag", tag, CIMKeyBinding::STRING));

    bindings.append(CIMKeyBinding(
        "CreationClassName", "Benchmark4", CIMKeyBinding::STRING));

    instance.setPath(CIMObjectPath(
        objectPath.getHost(),
        objectPath.getNameSpace(),
        "Benchmark4",
        bindings));
}

static CIMInstance _create_Benchmark(
    const char* tag)
{
    CIMInstance ci("Benchmark4");

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

    ci.addProperty(CIMProperty("CreationClassName", String("Benchmark4")));

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

    return ci;
}

Benchmark4Provider::Benchmark4Provider()
{
}

Benchmark4Provider::~Benchmark4Provider()
{
}

void Benchmark4Provider::initialize(Pegasus::CIMOMHandle& cimom)
{
    try
    {
        for (size_t i = 0; i < NUM_INSTANCES; i++)
        {
            char buffer[32];
            sprintf(buffer, "Pegasus-%d", int(i));
            CIMInstance inst = _create_Benchmark(buffer);
            _instances.append(inst);
        }
    }
    catch (Exception& e)
    {
        std::cout << "Exception: " << e.getMessage() << std::endl;
    }

#if 0
    size_t size = memo_deep_size(&_instances, sizeof(_instances));
    printf("SIZE[%d]\n", (int)size);
#endif
}

void Benchmark4Provider::terminate()
{
}

void Benchmark4Provider::getInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::InstanceResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark4Provider::getInstance()");
}

void Benchmark4Provider::enumerateInstances(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::Boolean includeClassOrigin,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::InstanceResponseHandler& handler)
{
    for (size_t i = 0; i < NUM_INSTANCES; i++)
    {
        // Note: the instance must be cloned here since it must be filtered
        // by the propertyList parameter.
        CIMInstance inst = _instances[i].clone();

        CIMProperty cp = inst.getProperty(inst.findProperty("Tag"));
        String tag;
        cp.getValue().get(tag);

        _inject_object_path(objectPath, inst, tag);

        inst.filter(includeQualifiers, includeClassOrigin, propertyList);
        handler.deliver(inst);
    }
}

void Benchmark4Provider::enumerateInstanceNames(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    Pegasus::ObjectPathResponseHandler& handler)
{

    
}

void Benchmark4Provider::modifyInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMInstance& instance,
    const Pegasus::Boolean includeQualifiers,
    const Pegasus::CIMPropertyList& propertyList,
    Pegasus::ResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark4Provider::modifyInstance()");
}

void Benchmark4Provider::createInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    const Pegasus::CIMInstance& instance,
    Pegasus::ObjectPathResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark4Provider::createInstance()");
}

void Benchmark4Provider::deleteInstance(
    const Pegasus::OperationContext& context,
    const Pegasus::CIMObjectPath& objectPath,
    Pegasus::ResponseHandler& handler)
{
    throw Pegasus::CIMNotSupportedException(
        "Benchmark4Provider::deleteInstance()");
}

extern "C" PEGASUS_EXPORT 
Pegasus::CIMProvider* PegasusCreateProvider(const Pegasus::String& name)
{
    if (name == "Benchmark4_Provider")
        return new Benchmark4Provider();

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Benchmark4/Benchmark4Provider.cpp,v 1.3 2007/03/07 19:12:42 mbrasher-public Exp $");

#include "Benchmark3_Provider.h"

#define NUM_INSTANCES 100

extern size_t memo_deep_size(const void* ptr, size_t size);

CIMPLE_NAMESPACE_BEGIN

static Benchmark3* _create_Benchmark3(const char* tag)
{
    Benchmark3* p = Benchmark3::create();

    p->Caption.value = "Caption";
    p->Description.value = "Description";
    p->ElementName.value = "ElementName";
    p->InstallDate.value = Datetime::now();
    p->Name.value = "Name";
    p->OperationalStatus.value.append(1);
    p->StatusDescriptions.value.append("StatusDescriptions");
    p->Status.value = "Status";
    p->Tag.value = tag;
    p->CreationClassName.value = "Benchmark3";
    p->Manufacturer.value = "Manufacturer";
    p->Model.value = "Model";
    p->SKU.value = "SKU";
    p->SerialNumber.value = "SerialNumber";
    p->Version.value = "Version";
    p->PartNumber.value = "PartNumber";
    p->OtherIdentifyingInfo.value = "OtherIdentifyingInfo";
    p->PoweredOn.value = true;
    p->ManufactureDate.value = Datetime::now();
    p->VendorEquipmentType.value = "VendorEquipmentType";
    p->UserTracking.value = "UserTracking";
    p->CanBeFRUed.value = true;
    p->RemovalConditions.value = 0;
    p->Removable.value = true;
    p->Replaceable.value = true;
    p->HotSwappable.value = true;
    p->Height.value = 1.0;
    p->Depth.value = 1.0;
    p->Width.value = 1.0;
    p->Weight.value = 100.0;
    p->HostingBoard.value = true;
    p->SlotLayout.value = "SlotLayout";
    p->RequiresDaughterBoard.value = false;
    p->SpecialRequirements.value = false;
    p->RequirementsDescription.value = "RequirementsDescription";
    p->OperatingVoltages.value.append(6);

    return p;
}

Benchmark3_Provider::Benchmark3_Provider()
{
}

Benchmark3_Provider::~Benchmark3_Provider()
{
}

Load_Status Benchmark3_Provider::load()
{
    for (size_t i = 0; i < NUM_INSTANCES; i++)
    {
        char buffer[32];
        sprintf(buffer, "CIMPLE-%d", int(i));

        Benchmark3* inst = _create_Benchmark3(buffer);
        _instances.append(inst);
    }

#if 0
        size_t size = memo_deep_size(&_instances, sizeof(_instances));
        printf("SIZE[%d]\n", (int)size);
#endif

    return LOAD_OK;
}

Unload_Status Benchmark3_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Benchmark3_Provider::get_instance(
    const Benchmark3* model,
    Benchmark3*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Benchmark3_Provider::enum_instances(
    const Benchmark3* model,
    Enum_Instances_Handler<Benchmark3>* handler)
{
    for (size_t i = 0; i < NUM_INSTANCES; i++)
        handler->handle(_instances[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Benchmark3_Provider::create_instance(
    const Benchmark3* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Benchmark3_Provider::delete_instance(
    const Benchmark3* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Benchmark3_Provider::modify_instance(
    const Benchmark3* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Benchmark3_Provider::IsCompatible(
    const Benchmark3* self,
    const CIM_PhysicalElement* ElementToCheck,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Benchmark3_Provider::ConnectorPower(
    const Benchmark3* self,
    const CIM_PhysicalConnector* Connector,
    const Property<boolean>& PoweredOn,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int Benchmark3_Provider::proc(
    const Registration* registration,
    int operation, 
    void* arg0, 
    void* arg1, 
    void* arg2, 
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef Benchmark3 Class;
    typedef Benchmark3_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "IsCompatible") == 0)
    {
        typedef Benchmark3_IsCompatible_method Method;
        Method* method = (Method*)arg2;
        return provider->IsCompatible(
            self,
            method->ElementToCheck,
            method->return_value);
    }
    if (strcasecmp(meth_name, "ConnectorPower") == 0)
    {
        typedef Benchmark3_ConnectorPower_method Method;
        Method* method = (Method*)arg2;
        return provider->ConnectorPower(
            self,
            method->Connector,
            method->PoweredOn,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Benchmark3/Benchmark3_Provider.cpp,v 1.5 2007/03/07 20:23:55 mbrasher-public Exp $");

#include "Benchmark1.h"

using namespace cimple;

static Benchmark1* _create_Benchmark(const char* tag)
{
    Benchmark1* p = Benchmark1::create();

    p->Caption.value = "Caption";
    p->Description.value = "Description";
    p->ElementName.value = "ElementName";
    p->InstallDate.value = Datetime::now();
    p->Name.value = "Name";
    p->OperationalStatus.value.append(1);
    p->StatusDescriptions.value.append("StatusDescriptions");
    p->Status.value = "Status";
    p->Tag.value = tag;
    p->CreationClassName.value = "Benchmark";
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

int main()
{
    for (size_t i = 0; i < 100000; i++)
    {
        Benchmark1* b = _create_Benchmark("Tag");
        Benchmark1::destroy(b);
    }

    return 0;
}


static void _test_upcalls()
{
    Ref<Fan> fan(Fan::create());
    Instance_Enumerator e;

    printf("===== cimom::enum_instances()\n");

    if (cimom::enum_instances("root/cimv2", fan.ptr(), e) == 0)
    {
        for (; e; e++)
            print(e().ptr());
    }

    printf("===== cimom::get_instance()\n");

    {
        Ref<Fan> keys(Fan::create());
        keys->DeviceID.value = "FAN01";
        Ref<Instance> inst = cimom::get_instance("root/cimv2", keys.ptr());
        print(inst.ptr());
    }

    printf("===== cimom::modify_instance()\n");

    {
        Ref<Fan> inst(Fan::create());

        inst->DeviceID.value = "FAN01";
        inst->Speed.value = 1111;
        inst->DesiredSpeed.value = 1111;
        int result = cimom::modify_instance("root/cimv2", inst.ptr());

        if (result != 0)
            printf("failed\n");
    }

    printf("===== cimom::get_instance()\n");

    {
        Ref<Fan> keys(Fan::create());
        keys->DeviceID.value = "FAN01";
        Ref<Instance> inst = cimom::get_instance("root/cimv2", keys.ptr());
        print(inst.ptr());
    }

    printf("===== cimom::delete_instance()\n");

    {
        Ref<Fan> key(Fan::create());
        key->DesiredSpeed.value = 1111;
        int result = cimom::delete_instance("root/cimv2", key.ptr());

        if (result != 0)
            printf("cimom::delete_instance() failed\n");
    }

    printf("===== cimom::get_instance()\n");

    {
        Ref<Fan> keys(Fan::create());
        keys->DeviceID.value = "FAN01";
        Ref<Instance> inst = cimom::get_instance("root/cimv2", keys.ptr());

        if (inst)
            print(inst.ptr());
        else
            printf("cimom::get_instance() failed\n");
    }
}

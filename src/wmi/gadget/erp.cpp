{
    __log("==== Upcall_Provider::upcalls()");

    // Check identity of self:

    if (self->key.value != 100)
    {
        __log("Upcall_Provider::upcalls():1");
        return_value.set(1);
        return INVOKE_METHOD_OK;
    }

    // cimom::enum_instances()

    Instance_Enumerator e;
    Widget* widget = Widget::create();
    uint32 sum = 0;

    if (cimom::enum_instances("root/default", widget, e) == 0)
    {
        for (; e; e++)
        {
            Ref<Instance> inst = e();

            Widget* w = cast<Widget*>(inst.ptr());

            if (w)
            {
                sum += w->key.value;
                __log("Upcall_Provider::upcalls(): key=%s", w->key.value);
            }
        }
    }

    if (sum != 300)
    {
        __log("Upcall_Provider::upcalls():2");
        return_value.set(2);
        return INVOKE_METHOD_OK;
    }

    // cimom::get_instance()

    widget->key.set(100);

    Ref<Instance> inst = cimom::get_instance("root/default", widget);

    if (!inst)
    {
        __log("Upcall_Provider::upcalls():3");
        return_value.set(3);
        return INVOKE_METHOD_OK;
    }

    return_value.set(0);
    return INVOKE_METHOD_OK;
}

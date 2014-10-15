
extern "C" int cimple_provider(
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
    switch (operation)
    {
	case OPERATION_GET_META_CLASS:
	{
	    *((Meta_Class**)arg0) = (Meta_Class*)&CLASS::static_meta_class;
	    return GET_META_CLASS_OK;
	}

	case OPERATION_CREATE_PROVIDER:
	    return CREATE_PROVIDER_OK;

	case OPERATION_DESTROY_PROVIDER:
	    return DESTROY_PROVIDER_OK;

	case OPERATION_LOAD:
	    return LOAD_OK;

	case OPERATION_UNLOAD:
	    return UNLOAD_OK;

	case OPERATION_TIMER:
	    return TIMER_CANCEL;

	case OPERATION_GET_REPOSITORY:
	{
	    const Meta_Class* const** meta_classes = 
		(const Meta_Class* const**)arg0;

	    size_t* num_meta_classes = (size_t*)arg1;

	    cimple_repository(*meta_classes, *num_meta_classes);
	    return GET_REPOSITORY_OK;
	}

	case OPERATION_GET_INSTANCE:
	    return GET_INSTANCE_UNSUPPORTED;

	case OPERATION_ENUM_INSTANCES:
	{
	    PROVIDER* provider = (PROVIDER*)arg0;

	    Enum_Instances_Handler<CLASS> handler(
		(Enum_Instances_Proc)arg2, (void*)arg3);
		    
	    Enum_Instances_Status status = provider->enum_instances(
		(const CLASS*)arg1, &handler);

	    handler._proc(0, status, handler._client_data);

	    return status;
	}

	case OPERATION_CREATE_INSTANCE:
	    return CREATE_INSTANCE_UNSUPPORTED;

	case OPERATION_DELETE_INSTANCE:
	    return DELETE_INSTANCE_UNSUPPORTED:

	case OPERATION_MODIFY_INSTANCE:
	    return MODIFY_INSTANCE_UNSUPPORTED:

	default:
	    return -1;
    }
}

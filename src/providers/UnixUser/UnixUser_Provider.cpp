#include "UnixUser_Provider.h"
#include <sys/types.h>
#include <pwd.h>

#define BUFFER_LENGTH 4096

CIMPLE_NAMESPACE_BEGIN

UnixUser_Provider::UnixUser_Provider()
{
}

UnixUser_Provider::~UnixUser_Provider()
{
}

Load_Status UnixUser_Provider::load()
{
    return LOAD_OK;
}

Unload_Status UnixUser_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status UnixUser_Provider::get_instance(
    const UnixUser* model,
    UnixUser*& instance)
{
    passwd pw;
    passwd* pwp;
    char buffer[BUFFER_LENGTH];

    setpwent();

    while (getpwent_r(&pw, buffer, BUFFER_LENGTH, &pwp) == 0)
    {
	if (model->name.value == pw.pw_name)
	{
	    instance = UnixUser::create();

	    instance->name.value = pw.pw_name;

	    if (model->password.null)
		instance->password.null = true;
	    else
		instance->password.value = pw.pw_passwd;    

	    if (model->uid.null)
		instance->uid.null = true;
	    else
		instance->uid.value = pw.pw_uid;    

	    if (model->gid.null)
		instance->gid.null = true;
	    else
		instance->gid.value = pw.pw_gid;    

	    if (model->fullName.null)
		instance->fullName.null = true;
	    else
		instance->fullName.value = pw.pw_gecos;    

	    if (model->homeDir.null)
		instance->homeDir.null = true;
	    else
		instance->homeDir.value = pw.pw_dir;    

	    if (model->shellProgram.null)
		instance->shellProgram.null = true;
	    else
		instance->shellProgram.value = pw.pw_shell;

	    return GET_INSTANCE_OK;
	}
    }

    endpwent();

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status UnixUser_Provider::enum_instances(
    const UnixUser* model,
    Enum_Instances_Handler<UnixUser>* handler)
{
    passwd pw;
    passwd* pwp;
    char buffer[BUFFER_LENGTH];

    setpwent();

    while (getpwent_r(&pw, buffer, BUFFER_LENGTH, &pwp) == 0)
    {
	UnixUser* instance = UnixUser::create();

	instance->name.value = pw.pw_name;

	if (model->password.null)
	    instance->password.null = true;
	else
	    instance->password.value = pw.pw_passwd;    

	if (model->uid.null)
	    instance->uid.null = true;
	else
	    instance->uid.value = pw.pw_uid;    

	if (model->gid.null)
	    instance->gid.null = true;
	else
	    instance->gid.value = pw.pw_gid;    

	if (model->fullName.null)
	    instance->fullName.null = true;
	else
	    instance->fullName.value = pw.pw_gecos;    

	if (model->homeDir.null)
	    instance->homeDir.null = true;
	else
	    instance->homeDir.value = pw.pw_dir;    

	if (model->shellProgram.null)
	    instance->shellProgram.null = true;
	else
	    instance->shellProgram.value = pw.pw_shell;

	handler->handle(instance);
    }

    endpwent();

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status UnixUser_Provider::create_instance(
    const UnixUser* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status UnixUser_Provider::delete_instance(
    const UnixUser* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status UnixUser_Provider::modify_instance(
    const UnixUser* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int UnixUser_Provider::proc(
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

    typedef UnixUser Class;
    typedef UnixUser_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

#include "Hello_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Hello_Provider::Hello_Provider()
{
}

Hello_Provider::~Hello_Provider()
{
}

Load_Status Hello_Provider::load()
{
    cimom::allow_unload(true);
    return LOAD_OK;
}

Unload_Status Hello_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Hello_Provider::get_instance(
    const Hello* model,
    Hello*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Hello_Provider::enum_instances(
    const Hello* model,
    Enum_Instances_Handler<Hello>* handler)
{
    // Create three instances and add them to the map.

    //
    // test the acquisition of username from the cimom.  This code
    // gets the username and if valid adds the name to the test of
    // the message property for the first instance. NOTE: This
    // Test should be moved to more permanent place in future
    //
    String username;

    String firstMessage("First Message");

    if (cimom::get_username(username))
    {
        CIMPLE_INFO(("Hello Provider username Exists\n"));
        if (username.size() != 0)
        {
            CIMPLE_INFO(("Hello Provider. username = %s\n", username.c_str()));
            firstMessage.append(". User name = ");   
            firstMessage.append(username);
        }
        else    // returned username but empty
        {
            firstMessage.append(". User name empty\n");
        }
        
    }
    else    // get_username returned error code
    {
        CIMPLE_INFO(("Hello Provider.No username found. Error rtnd\n"));
    }
    
    // 
    // As a demonstration attach the input namespace from the model for the
    // request to the Message text and log the information.
    //

    CIMPLE_INFO(("Hello Request Namespace %s\n", model->__name_space.c_str()));
    firstMessage.append(", Request in Namespace ");
    firstMessage.append(model->__name_space);

    {
        Hello* instance = Hello::create();
        instance->Key.value = "Key01";
        instance->Message.value = firstMessage;
        handler->handle(instance);
    }
    {
        Hello* instance = Hello::create();
        instance->Key.value = "Key02";
        instance->Message.value = "Second Message.";
        handler->handle(instance);
    }

    {
        Hello* instance = Hello::create();
        instance->Key.value = "Key03";
        instance->Message.value = "Third Message.";
        handler->handle(instance);
    }
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Hello_Provider::create_instance(
    Hello* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Hello_Provider::delete_instance(
    const Hello* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Hello_Provider::modify_instance(
    const Hello* model,
    const Hello* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

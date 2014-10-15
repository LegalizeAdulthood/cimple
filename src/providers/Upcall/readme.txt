This provider is a simple example of an extension defined starting
with CIMPLE 1 and extended in CIMPLE 2.01, the CIMPLE defined upcall. 

CIMPLE version 1 include the upcall instance operations (getInstance,
enumerateInstance, etc.) and CIMPLE 2.01 extended this to include
invokeMethod. 

The goal of the CIMPLE upcall instance operation is to allow instance 
calls back to the cimserver which will return CIMPLE instances for use in 
a provider.  It is primarily used to acquire instances from elsewhere in 
the cim server either to use selected properties in instances of the 
provider target class or to create associations based on the instances 
from other providers.  

Creating an upcall involves the following steps:

1. Define with genclass the Classes for which there will be upcalls.

   Thus, in this example, there will be an upcall for CIM_Computer system.

   For the example, the genclass call is:

	genclass -r Upcall CIM_ComputerSystem
	
This causes class meta data to be generated for both the target provider 
(Upcall) and for the other classes referenced by the target class.  In 
this case since CIM_ComputerSystem is part of a class hiearchy in the CIM 
model, metadata is generated for all of the elements of the Class 
hiearchy/accesabilty chain including: 
	CIM_ComputerSystem
	CIM_ConcreteJob
	CIM_EnabledLogicalElement
	CIM_Job
	CIM_LogicalElement
	CIM_ManagedElement
	CIM_MagagedSystemElement
	CIM_System

2. Generate the Upcall provider with genprov and genmod.  Note that there is
   no reference to the Upcall classes in either genprov or genmod. For this
   example, the commands to be executed are:

	genprov Upcall

	genmod Upcall Upcall

   Note that this does not generate a CIM_ComputerSystem provider.

3. Implement the Upcall_Provider including both the instance functions. for 
   the upcall and the upcall functions for CIM_ComputerSystem.

4. Implement the Upcall functions for CIM_ComputerSystem.  The upcall interface
   is part of the cimom class and includes functions for:
	  * enumerate_instances (enum_instances)
	  * get_instance
	  * create_instance
	  * delete_instance
	  * modify_instace
	  * invoke_method
   
   The upcall mechanism does not support references or association
   operations.

   An upcall is implemented as a combination a) creation of a model object
   b) execution of the upcall, c) evaluation of the iteration of returned
   instances.

   The following is an example of an upcall that returns an array of
   CIM_ComputerSystem CIMPLE instances.

         /* Execute the upcall to CIM_Computer system and return an array
            of CIMPLE CIM_ComputerSystem* instances
         */

	static int _enum_CIM_ComputerSystem()
	{
	    // Create the cimple Model for CIM_ComputerSystem
	    CIM_ComputerSystem* model = CIM_ComputerSystem::create();
	
	    // Define the instance enumerator
	    Instance_Enumerator ie;
	
	    // Call the enumerate function for CIM_ComputerSystem
	    if (cimom::enum_instances("root/cimv2", model, ie) != 0)
		return -1;
	
	    // Iterate the responses.
	    for (; ie; ie++)
	    {
		// get the next iteration form the iterator
	
		Ref<Instance> inst = ie();
		
		// cast to an instance of CIM_ComputerSystem
	         
		CIM_ComputerSystem* ccs = cast<CIM_ComputerSystem*>(inst.ptr());
	
		// put it in the return array

		print(ccs);
	    }
	
	    return 0;
	}


    The provider implements the upcall both as a standalone function as shown 
    above and also as a function integrated into the enumerate instances so 
    that the iterator for the ComputerSystem enumerate acts as the controlling 
    loop to generate instances of the Upcall class using a property from the 
    ComputerSystem instance in each Upcall instance.  

    Within the enumerate instances function it is easy to implement the upcall
    so that the set of returned instances is used as the basis for the loop
    to create instances of our target class (Upcall).

    This simply involves injecting the call to get the instances and using
    the resulting enumerator as the loop driver to create Upcall instances as 
    follows:

    CIM_ComputerSystem* computer_system_model = CIM_ComputerSystem::create();

    Instance_Enumerator ie;
 
    if (cimom::enum_instances("root/cimv2", computer_system_model, ie) != 0)
        return ENUM_INSTANCES_OK;

    int upcall_key = 1;

    for (; ie; ie++)
    {  
        Ref<Instance> inst = ie();

        CIM_ComputerSystem* ccs = cast<CIM_ComputerSystem*>(inst.ptr());
        
        Upcall* upcall = Upcall::create(true);
        upcall->key.set(upcall_key++);

        String name = ccs->Name.value;
        upcall->ComputerSystemName.set(name);
        printf("Generate instance for %s\n",(const char*)name.c_str());

        handler->handle(upcall);
    }

    return ENUM_INSTANCES_OK;

5   Compile install and register the provider. Remember only the Upcall
    provider is registered.  The upcall provider has been registered
    elsewhere.


 

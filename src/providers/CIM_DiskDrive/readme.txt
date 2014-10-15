This provider implements the  DMTF CIM_DiskDrive Class directly.  It uses the
currently defined DMTF mof directly without adding any additional classes
through repository.mof.

This implementation does not do any useful work in that only the default
behavior is defined for the DiskDrive class.

Note that it defines other classes with relationships to DiskDrive including:

CIM_MediaAccessDevice
CIM_ManagedSystemElement
CIM_LogicalElement
CIM_LogicalDevice
CIM_Job
CIM_EnabledLogicalElement
CIM_ConcreteJob

This is primarily a demonstration of implementing this class with its superclass
hiearchy directly and does not indicate good behavior.  In general you should be careful in using this classs since it may override existing providers for the
same classes.

Note that  it is not recommenended that the provider directly implement
the CIM Classes.  The user should create subclasses.

No test is implemented for this provider.

This provider is a test for the passage of all cim types between
provider and client.  It tests the creation of instances with all
scalar and array cim types and tests to assure that the values
returned to the client with a subsequent get are the same.  

It also tests for NULL property value transfer. Note that since it
tests Null properties for both send and return and when sending,
pegasus, at least, simply does not send the property, it is really
determining that properties defined as null for the createInstance
are not returned at all.

This provider does NOT test any issues of subclassing (local only,
etc.).  It also does not test for use of the include qualifiers 
parameter as part of the operation since this has been deprecated.

The Client for this test is in the subdirectory TestAll. That client
creates an instance of All_Class, gets that instance and confirms 
all property values, creates an instance with almost all NULL
properties and gets the instance for confirmation. Then it gets
the instance with property lists of varying sizes and confirms that
only the correct properties are returned and with the correct values.

It also tests parameters with all of the CIM data types.

The conclusion of a test with the provider is that all of the CIM data
types are correctly handled both in creation and getInstance and in 
both IN and OUT parameters.

The provider actually creates another instance internally that is
available through the enumerateInstances to confirm that an instance
internally generated creates correct values for the CIM data types.



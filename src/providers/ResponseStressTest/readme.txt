This provider defines a provider for which both the number of responses
and size of each response instance can be dynamically defined using the
set method of the class CMPL_ResponseStressTest.

It was defined to allow testing with large responses both for functionality
and to measure response times.

There is a client that supports this testing and specifically testing with
a corresponsing Pegasus C++ provider TST_ResponseStressTest if that 
provider is installed in Pegasus.

Normally to use this provider, the client should:

1. Execute the set method to set the instance size and number of instances
to be returned in each enumerate response
2. Execute the enumerateInstances operation.

The provider will return the defined number of instances with the defined
size (approximately). 

In addition the provider calculates information about the time between each
instance issued to help the user understand delays encountered in the server
(i.e. delays that the server imposes before returning from the deliver
operation for each instance delivered by the provider.  It also delivers
a total time from the start of the operation so that the user can estimate
the total time the provider took from beginning to end (minus the delivery
time for the last instance delivered).

Note that the variables set by the set method are NOT persistent. They will
be reset to a default each time the provider is started.



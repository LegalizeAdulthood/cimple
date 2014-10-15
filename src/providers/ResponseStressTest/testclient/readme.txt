This is a test client for the ResponseStressTest provider.

It is capable of 3 different operations

1. make (No parameter on commmand line) - Conducts a basic test of the provider
testing the set, get, and enumeration operations.  This is the mode use
in the live test for this provider.

2. make one -  Executes a single  of both this provider
for response time and the corresponding pegasus provider (if that provider
exists).  This is a test of the operation of the provider and its table output
for both the CIMPLE provider and the corresponding pegasus provider

3. make test - Conducts an extensive test of the two providers over a range
of instance sizes and number of instances returned.  This is presented as
a table showing the various times measured (server, client app, etc.) to
help determine the realative response time for pegasus and CIMPLE providers.

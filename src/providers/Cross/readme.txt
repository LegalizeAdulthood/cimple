This sample provider illustrates and tests a cross-namespace association
provider.

This test implements 4 providers:

    * Left   Simple class with one property
    * Right - Simple class with one property
    * Cross -instance with Left in the Left Namespace and Right in the 
      Right Namespace and other instances with the instances in the 
      same namespace.
    * CrossSubclass - This is a subclass of Cross to assure that the
      characteristics apply to the subclass of the associations

The test registers:

Cross, Left, Right, CrossSubClassin both namespaces

The test itself is implemented in the subdirectory testclient.








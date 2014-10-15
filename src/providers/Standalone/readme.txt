This directory contains a "standalone" provider. That is, one that does not
depend on an external repository library. We generate a single class (called
Standalone) with the following command (the class is defined in repository.mof).

        % genclass -r Standalone

Next we generate the provider:

        % genprov Standalone

And then we create module.cpp.

Finally we link it all toghether.

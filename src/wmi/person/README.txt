Creating the Person Provider
17 Dec 2008


This is a very simple single class sample provider defined just to be used
with wmi.  It demonstrates a provider definition, creation, and installation.

The provider implements a single class (Person) with several properties and
as single method.  It includes the extra qualifiers (provider, dynamic, and
implemented) that are required by a wmi class for proper registration and
operation routing. See providerclasses.mof

Note that the includes these extra qualifiers required by wmi as part of
the repository.mof so that the standard CIM_Qualifiers file distributed by
DMTF can be used without modification to compile wmi providers. They
are defined in wmiqualifiers.mof and repository.mof defines the includes
to compile both these qualifiers and the providerclasses.mof files.

The provider can be created by the following steps:

1. Set the CIMPLE_MOF_PATH variable
   [c:...\Person] set CIMPLE_MOF_PATH=\dev\cimple\Schemas\cim214

2. Generate the provider. Targets are defined in the Makefile to do this

   [c:...\Person] make genclass
   [c:...\Person] make genprov
   [c:...\Person] make genmod

3. Compile the provider

   [c:...\Person] make

4. Register and install the provider with wmi. Sample registration is 
   included in the Makefile

   [c:...\Person] make regwmi

5. The provider should generate two instances of the Person class. Which can
   verified with wmi client tools such as wmitest, wbemtest, etc.


NOTE: The sample Makefile specifically puts the Person class and the 
   registration into the root/cimv2 namespace

   The Makefile does not provide a way to completely remove the provider
   and registration. 

17 Dec 2008


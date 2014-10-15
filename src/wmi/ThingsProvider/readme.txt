This test provider demonstrates multiple CIMPLE providers within a single shared library (module).

The providers are Thing1 and Thing2.  The module is named ThingsProvider.

The special manual step for this provider is that the register.mof must reflect the provider module
name, not the provider class names.  However, note that the instance and method provider registration
as defined for WMI in the register.mof applies to all class providers in that provider module.

In particular, WMI class providers (defined as a single CIMPLE provider) are not registered separatly.
Only the module is registered.  Any number of providers can be defined under a single provider module.
The actual wmi calls (CreateInstanceEnumAsync) defines the class to be enumerated.   Within
the WMI_Adapter, CIMPLE handles this by attemping to lookup the CIMPLE provider corresponding to the
class provided in the call.



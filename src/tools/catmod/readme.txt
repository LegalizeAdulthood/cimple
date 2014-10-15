Display information built into provider modules by CIMPLE that is part
of the CIMPLE registration process using regmod.  This information
includes the providers and their types and classes served and entry point.

Example
%%>catmod libcimpleLamp.so 

Produces the following output:

=== Providers:
    [Lamp_Module:LampLink_Provider:association:LampLink]
    [Lamp_Module:LampIndic_Provider:indication:LampIndic]
    [Lamp_Module:Lamp_Provider:instance:Lamp]

=== Entry points:
    PegasusCreateProvider()


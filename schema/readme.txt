This directory contains versions of the CIM schema. To change the version of
the schema used by CIMPLE, define this variable in your environment to point
to the full path of the desired schema directory.

    export CIMPLE_SCHEMA_PATH=/opt/cimple/schema/cim211

Also, don't forget to define CIMPLE_MOF_PATH (used by genclass and genprov).

    export CIMPLE_MOF_PATH=$(CIMPLE_SCHEMA_PATH):/other/dirs

The schema directories that end in "_experimental" are from the DMTF
experimental distribution. They contain all the non-experimental classes
as well.

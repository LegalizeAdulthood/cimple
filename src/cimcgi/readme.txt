NOTE: CIM-CGI is broken in this release. It will be restored in a subsequent
release. The problem is that it depends on having a cimple_repository()
entry point, which has been eliminated for now. A way of defining such
an entry point as part of a meta-repository and associating it with a CIM-CGI
module will solve this problem.

SYNOPSIS:
=========

This directory contains the experimental CIM-CGI provider, which allows one
to write simple read-only instance providers using a scripting language (such
as Perl, Python, Bash, etc.) or using any other programming language. Like
CGI, familiar to WEB developers, CIM-CGI programs pass their responses to the
server strictly through standard output.

EXAMPLES:
=========

The following is a simple provider that provides two instances.

    #!/bin/sh
    echo "SSN=444556666"
    echo "FirstName=Jane"
    echo "LastName=Doe"
    echo ""
    echo "SSN=44455777"
    echo "FirstName=John"
    echo "LastName=Doe"
    echo ""

It writes the following to standard output.

    SSN=444556666
    FirstName=Jane
    LastName=Doe
    <LF>
    SSN=44455777
    FirstName=John
    LastName=Doe
    <LF>

Note that properties are simple name-value pairs. Instances are terminated
by a linefeed character. The corresponding MOF definition is defined as
follows.

    class Contact
    {
        [Key] uint32 SSN;
        stirng FirstName;
        stirng LastName;
    };

Ass with all CIMPLE providers, a corresponding C++ class must be generated
from this defintin with the genclass utility and placed in a repository
module.

Here is a second provider, that provides the entries in the /etc/passwd file.

    #!/bin/sh
    SCRIPT=`cat<<END
        {
            print "name="\\$1;
            print "uid="\\$3;
            print "gid="\\$4;
            print "fullName="\\$5;
            print "homeDir="\\$6;
            print "shellProgram="\\$7;
            print "";
        }
    END
    `
    awk -F ":" "$SCRIPT" /etc/passwd

REGISTRATION:
=============

Before registering a CIM-CGI provider, set the CIMCGI environment variable
to the full path of the directory containing the CIM-CGI programs. Each
program begins with the name of the class being provided followed by a '.'
character. For example, the Contact provided shown above, may be have one
of the following names:

    Contact
    Contact.sh
    Contact.bash

Next, run the regmod utility on the CIM-CGI provider library as follows.

    regmod /home/jdoe/cimple/lib/libcmplcimcgi.so

This scans the $CIMCGI directory and registers each provider (cgi-program) it
finds.

LIMITATIONS:
============

1.  The current implementation does not handle array property types.

2.  Association providers are not supported.

3.  Error reporting is incomplete. Registration errors are ignored for now.

FUTURE DIRECTIONS:
==================

1.  Consider whether GET-INSTANCE can be implemented more efficiently
    by passing keys to the program, perhaps in the following format.

        key1=value1,key2=value2

    For example:

        ssn=44455777

2.  Consider whether CGI providers should be extended to handle more
    operations, such as CREATE-INSTANCE or MODIFY-INSTANCE.

3.  Consider whether some analogue to "FastCGI" is worthwhile (this will
    allow a program to be loaded once and invoked multiple times).

NOTES:
======

1.  See cimcgi directory (under the current directory). It contains some
    examples.

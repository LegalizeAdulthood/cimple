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

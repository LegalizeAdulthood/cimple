
This provider implements two methods:

    SetTime()
    GetTime()

Call SetTime() to set the current time for the provider.

Call GetTime() to get the current time for the provider.

To test use:

   the ciminvoke test client with command lines like:

    $ ciminvoke CMPL_Time SetTime Time=20070101120000.123456-360
    $ ciminvoke CMPL_Time GetTime return=1000

    NOTE: ciminvoke is in the src/pegasus/utils directory but is not
    normally installed with a cimple make and make install.   Enable
    it to run these tests.  These commands can be executed with
    make manual-test

    or

    The test program in the InvokeTime subdirectory of this
    directory which sends a time to the provider with one method and
    retrieves time from the provider with a second method.

This provider is installed as part of the automated tests and the
invokemethod program is used to test the provider.



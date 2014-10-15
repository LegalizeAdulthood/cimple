
This provider implements two methods:

    SetTime()
    GetTime()

Call SetTime() to set the current time for the provider.

Call GetTime() to get the current time for the provider.

To test use:

    $ ciminvoke CMPL_Time GetTime Time=20070101120000.123456-360
    $ ciminvoke CMPL_Time GetTime return=1000


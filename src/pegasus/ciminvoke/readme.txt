                                Ciminvoke

Synopsis:
=========
 
Ciminvoke is a utility to request the Pegasus CIM server to invoke extrinsic
methods.

Introducation:
==============

In general the utility is run like this.

    ciminvoke [OPTIONS] object-path method-name [param=VALUE]...

Here is a typical usage scenario. Suppose you want to invoke a method of
the "Methods" class. The first step is to find out which methods that
class supports. Type the following to find out (-p means "print").

    % ciminvoke -p Methods
    foo()
    foo2()
    foo3()
    foo4()

This shows that the Methods class supports three methods. To find out what
arguments the foo() method takes, we type this.

    % ciminvoke -p Methods foo
    string foo(
        [In(true), Out(false)] uint32 arg1,
        [In(true), Out(false)] string arg2,
        [In(true), Out(false)] boolean arg3,
        [In(true), Out(true)] uint32 arg4,
        [In(true), Out(true)] string arg5,
        [In(true), Out(true)] boolean arg6);

Now we know the method signature. To call foo, do this.

    % ciminvoke Methods.key=1 foo arg1=100 arg2=Hello arg3=false
    return=thanks for calling
    arg4=999
    arg5=nine hundred ninety-nine
    arg6=false

The function prints the return value first, followed by each of the output
arguments (one per line).

Next we consider how to call a method that takes an object path. To see the
method signature, do this.

    % ciminvoke -p Methods.key=1 foo2
    string foo2(
        [In(true), Out(false)] Arg REF arg1,
        [In(true), Out(true)] Arg REF arg2);

We call foo2() like this.

    % ciminvoke Methods.key=1 foo2 arg1=Arg.key=99
    return=thanks
    arg2=root/cimv2:Arg.key=12345

Finally we consider how to invoke methods with array parameters. The method
foo4() has array parameters.

    % ciminvoke -p Methods foo4
    uint32 foo4(
        [In(true), Out(false)] string arr1[],
        [In(true), Out(true)] string arr2[]);

To invoke it, we repeat the the array parameter for each element of the array.
For eample.

    % ciminvoke Methods.key=1 foo4 arr1=red arr1=green arr1=blue
    return=999
    arr2=red
    arr2=green
    arr2=blue

Escaping of quotes:
===================

Quotes rarely are needed but objects paths may require quotes for string
key values since the quotes are part of the data. For example:

        MyClass.key1="hello"

On Windows, the quotes are preserved and are passed on to the server. On
Unix the quotes would be removed before that string is passed to ciminvoke
and would be converted to this.

        MyClass.key1="hello"

Therefore, on Unix you must escape the quotes.

        MyClass.key1=\"hello\"

Note that preservation of quotes is only needed when you really want the
quotes to be passed on to the server. For example, the following (on Unix)
passes a string property whose value includes the quotes.

        arg1=\"hello\"

Which may not be what you intended. Instead, you might want this.

        arg1=hello

Examples:
=========

% ciminvoke CIM_StoragePool.InstanceId=\"88\" GetAvailableExtents Goal=CIM_StorageSetting.InstanceID=\"99\" AvailableExtents=CIMStorageExtent.DeviceID=\"1\",CreationClassName=\"MyStorageExtent\",SystemName=\"localhost\" AvailableExtents=CIMStorageExtent.DeviceID=\"2\",CreationClassName=\"MyStorageExtent\",SystemName=\"localhost\"

% ciminvoke Methods.key=1 foo arg1=100 arg2=hello arg3=false

% ciminvoke Methods foo2 arg1=Arg.key=99

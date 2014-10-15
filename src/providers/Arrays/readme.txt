This provider implements a simple class with only a key property.
a property that returns the number of elements in each array property, and
array based properties for several data types.

It also includes a single method to allow the number of elements to be
returned in each array to be set (setReturnCount).

The provider implements only enumerate_instance and uses the defaults
to implement get_instance.

The provider returns a single instance of the class with 100 elements
in arrays of several data types, building the instance to be returned on
the fly.

There is a live test target using cimcli and a manual test target in
the Makefile


This provider implements a simple class with only a key property
and  property that of Uint16 elements.

The provider implements only enumerate_instance and uses the defaults
to implement get_instance.

The provider returns a single instance of the class with 100 elements
in the array.

There is a live test target using cimcli and a manual test target in the Makefile


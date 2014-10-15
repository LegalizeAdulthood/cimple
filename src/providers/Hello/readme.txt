This is a very simple provider that simple returns a set of static instances.

It exists primarily because it was one of the early providers defined during
CIMPLE development.

It has been modified to provide at least execution of the allow_unload and
get_username functions.

However, there are at this point no automated tests for this provider and
no automated test for the allow_unload() and get_username() functions.

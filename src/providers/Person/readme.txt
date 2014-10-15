This directory contains an implementation of the 'Person' provider. It
implements:

	Person instance provider
	Salesman instance provider
	PersonLink association provider
	SalesmanLink Association provider

The Person provider and PersonLink provider were implemented with the
Instance_Map cache as a demonstration of this function with all of the
CIM Operation implemented directly in map calls.

Note that this is an update in Nov 09. The earlier version used the
Map but not the map CIM Operation calls.

The PersonLink provider defines four associations:

	P1 <-- parent.child --> P3
	P1 <-- parent.child --> P4
	P2 <-- parent.child --> P3
	P2 <-- parent.child --> P4

To register provider with Pegasus:

	% make regmod

To test:
        make live


	% cimcli gi Person
	% cimcli ei Person
	% cimcli ni Person
	% cimcli gi Person.ssn=2
	% cimcli di Person.ssn=2



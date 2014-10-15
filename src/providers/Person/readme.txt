This directory contains an implementation of the 'Person' provider. It
implements:

	Person instance provider
	Link association provider

The Linke provider defines four associations:

	P1 <-- parent.child --> P3
	P1 <-- parent.child --> P4
	P2 <-- parent.child --> P3
	P2 <-- parent.child --> P4

To register provider with Pegasus:

	% make reg

To test:

	% CLI gi Person
	% CLI ei Person
	% CLI ni Person
	% CLI gi Person.ssn=2
	% CLI di Person.ssn=2
	% create_person
	% modify_person

In Pegasus you will have to do the following from the Pegasus root:

	% make repository
	% cimserver -s; cimserver

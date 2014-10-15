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

	% cimcli gi Person
	% cimcli ei Person
	% cimcli ni Person
	% cimcli gi Person.ssn=2
	% cimcli di Person.ssn=2
	% create_person
	% modify_person

In Pegasus you will have to do the following from the Pegasus root:

	% make repository
	% cimserver -s; cimserver


Apriori generates a no-collision hash function for a set of input strings
which are known apriori. N input strings are mapped perfectly onto integers 
in the range 0 to N-1. The generated hash function is defined as follows.

	int hash(const char* p, size_t n);

P is a pointer to the string in question and n is the length of some prefix
of the string which may potentially be one of the string from the apriori
set. If the string is found, the corresponding index is returned. Otherwise,
negative one is returned.

The usage is as follows.

	% apriori apriori-spec-file

The specification file is read and the hash function (written in ANSI C) is 
written to standard output. Also, an enumerated type is written whose tags
correspond to string in the input set.

The specification file lines have the following form:

	<string>:<identifier>

The string is one of the apriori strings in the hash table. The identifier
becomes the enumeration tag name whose value is an integer in the range
0 to N-1 where N is the number of strings. Here's an example specification
file:

	Sunday:SAT
	Monday:MON
	Tuesday:TUE
	Wednesday:WED
	Thursday:THU
	Friday:FRI
	Saturday:SAT

For this specification file, apriori generates the following code:

	enum
	{
	    SUN = 0;
	    MON = 1;
	    TUE = 2;
	    WED = 3;
	    THU = 4;
	    FRI = 5;
	    SAT = 6;
	};

	int hash(const char* p, size_t n)
	{
	    size_t code = n + p[0] + p[n-1];

	    switch(code)
	    {
		case 197:
		    if (equal("Friday", 6, p, n))
			return FRI;
		case 204:
		    if (equal("Monday", 6, p, n))
			return MON;
		case 210:
		    if (equal("Sunday", 6, p, n))
			return SUN;
		case 212:
		    if (equal("Tuesday", 7, p, n))
			return TUE;
		    if (equal("Saturday", 8, p, n))
			return SAT;
		case 213:
		    if (equal("Thursday", 8, p, n))
			return THU;
		case 217:
		    if (equal("Wednesday", 9, p, n))
			return WED;
		default:
		    return (size_t)-1;
	    }
	}

/*
	Implement an integer parser in the shortest code possible, 
	with the following restrictions:
		* The function or program can only take one argument: 
		  a string (or equivalent). Assume it to be signed and 
		  always valid (don't worry about decimals, etc.). 
		  The input may optionally omit the sign, in which 
		  it is assumed to be positive.
		* The function or program must output an integer (or equivalent).
		* No pattern matching, regular expressions, etc. are allowed. 
		  This includes utilities such as tr for *nix.
		* No string parsing utilities are permitted, even from the standard library. 
		  This includes, but is not limited to,  parseInt() from JavaScript, 
		  int() in Python, and Int32.parse() from VBScript.

		* The only permitted predefined string manipulation functions, methods, 
		  etc. fall into one of the following categories:
			- extract a substring (e.g. substr(), slice())
			- get code point from character, vice versa (e.g. toCodePoint(),  
			  fromCodePoint())
			- concatenate strings (e.g. append(),  concat(), strcpy())
		* No external libraries are permitted.

		* No string parsing utilities are permitted, even from the standard library.
		* Implicit conversion to string is disallowed (e.g. 1+'' in JavaScript)
*/

/*
	C - 69 
*/

c,r,m;p(char*s){for(m=2,r=0;c=15&*s++;r=c>9?m=r:r*10+c);return--m*r;}
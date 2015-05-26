/*
	Take a string of binary characters separated by a space, and convert it to an ASCII string.
	For example...
	"1001000 1100101 1101100 1101100 1101111 100000 1010111 1101111 1110010 1101100 1100100"
	Would convert to...
	"Hello World"
	The binary string will be stored in a variable called s.
*/

/*
	C - 63
	since C has no base 2 converter in standard library
	edit: there is, i'm just too stupid to know about it
*/

r;f(char*s){for(;*s;(*s|32)-32||(putchar(r),r=0))r=2*r|*s++&1;}

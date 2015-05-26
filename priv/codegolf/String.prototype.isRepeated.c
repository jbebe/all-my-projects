/*
	any of you must have heard that there is a cooler version of JavaScript in town (read ES6) which has a method String.prototype.repeat so that you can do
	"Hello, World!".repeat(3)
	and get
	"Hello, World!Hello, World!Hello, World!"
	as the output.
	Your job is to write a function or a program in a language of your choice which detects if a string has been gone under such transformation.
*/

/*
	C 85
*/
l,d;f(s){return l=strlen(s),strstr(d,strcpy(strcpy(d=alloca(l*2+1),s)+l,s)-1)-d-l+1;}

/*
	It turned out to be quite long but external functions are always like that. 
	It came to my mind that I could rewrite every string function 
	replacing them by a loop or a recursive one. But in my experience 
	it would turn out longer and frankly I don't want to try that out.
	After some research I saw solutions on high performance but 
	not as clever (and short) as xnor's one. just to be original... 
	i rewrote the same idea in c.
	
	explanation:
*/

int length, 
    duplicate;
int is_repetition(char *input)
{
    // length = "abc" -> 3
    length = strlen(input);
    // alloca because the function name is as long as "malloc" 
    // but you don't have to call free() because it uses the stack
    // to allocate memory
    // duplicate = x x x x x x + x
    duplicate = alloca(length*2 + 1);
    // duplicate = a b c 0 x x + x
    strcpy(duplicate, input);
    // duplicate = a b c a b c + 0
    strcpy(duplicate + length, input);
    if (strstr(duplicate,duplicate + length - 1) != duplicate + length - 1)
        // repetition
        // e.g. abab -> abababab -> aba[babab]
        // -> first occurence of [babab] is not aba[babab]
        // but a[babab]ab -> this is a repetition
        return 1;
    else
        // not repetition
        // e.g. abc -> abcabc -> ab[cabc]
        // -> first occurence of [cabc] is ab[cabc]
        // it matches the last "cabc"
        return 0;
}
/*
	Write a recursive function/program, to calculate either 
	the Factorial or the Fibonacci number of a given non-negative integer, 
	without explicitly implementing the base case(s).
	
	You cannot
		* Use if statement anywhere in your program/function, 
		  nor switch nor short-if-syntax (?:). Not even loops. 
		  Basically all control-flow statements are forbidden.
		* Use try, catch or exceptions of any kind.
		* Terminate the program (anything like exit(1)).
*/

int not_factorial(int n){return 1;}
int factorial(int n)
{
    int (*maybe_factorial[])(int) = {factorial, not_factorial};
    return n*maybe_factorial[!(n-1)](n-1);
}

/*
	This is inspired by a real world problem I had. 
	I'm curious to see if there is any clever way to go about this.
	You are given two unsorted arrays, A and B, each containing 
	an arbitrary number of floats. A and B don't necessarily have 
	the same lengths. Write a function that takes the elements 
	of A sequentially and finds the nearest value in array B. 
	The result has to be contained in a new array.
*/

/*
	C - 144 - multipurpose function!
*/

#define f float
f T, *C, m;
f *q(f *A, f *B, int S, f s)
{
    if(m) 
        return abs(T - *A) - abs(T - *B);
    for ( 
        C = malloc(S * 4);
        m = S--;
        C[S] = *B
    ) 
        T = A[S], 
        qsort(B, s, 4, q);
    return C;
}

/*
	example:
*/

float A[] = {1.5, 5.6, 8.9, -33.1};
float B[] = {-20.1, 2.2, 10.3};
float *C;

C = q(A, B, sizeof(A)/sizeof(*A), sizeof(B)/sizeof(*B));
// C holds 2.2,2.2,10.3,-20.1
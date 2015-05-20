#include "rendez.h"
#include <stdlib.h>

int cmpdbl(double *a, double *b){
	return ((*a > *b) ? -1 : ((*a == *b) ? 0 : 1));
}

void rendez(double t[], int n){
	qsort(t, n, sizeof(*t), cmpdbl);
}
#include "rendez.h"
#include <stdio.h>

int main(void)
{
	double penis[] = { 2.0, 1.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
	int i;

	for (i = 0; i < sizeof(penis) / sizeof(double); ++i)
	{
		printf("%.0f ", penis[i]);
	}
	puts("");
	rendez(penis, sizeof(penis) / sizeof(double));
	for (i = 0; i < sizeof(penis) / sizeof(double); ++i)
	{
		printf("%.0f ", penis[i]);
	}
	getchar();
	return 0;
}
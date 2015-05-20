#include <stdio.h>
#include <time.h>
#include <math.h>

float my_sin(float x)
{
	if ( x > 3.141592f )
	{
		x -= 4.712388f;
		return x * x * 0.405285f - 1;
	}
	x -= 1.570796f;
	return -(x * x * 0.405285f) + 1;
}

void main(void)
{
	int 
		j = 0;
	double	
		time_spent1,
		time_spent2,
		i = 0,
		output1 = 0;
	float 
		output2 = 0;
	clock_t 
		begin, 
		end;

	begin = clock();
	for (j = 0; j < 100000; j++){
		for (i = 0; i <= 6.28318530718; i += 0.006){
			output1 = sin(i);
		}
	}
	end = clock();
	time_spent1=(double)(end-begin)/CLOCKS_PER_SEC;

	begin = clock();
	for (j = 0; j < 100000; j++){
		for (i = 0; i <= 6.28318530718; i += 0.006){
			output2 = my_sin(i);
		}
	}
	end = clock();
	time_spent2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("sin(x) time:    %10f\n"
			"my_sin(x) time: %10f\n"
			"--------------------------\n",
			time_spent1,time_spent2);
	getchar();
}
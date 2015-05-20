#include <iostream>

void reverse(int *a, int len, int b){
	int temp;
	for(int i = 0; i < len; i+=b) {
		int j, k;
		for (j = i,k = j+b-1; j < k && k < len; j++, k--) {
			temp = a[j];
			a[j] = a[k];
			a[k] = temp;
		}
	}
}

int main(void){
	int test_a[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int test_b[] = {1, 2, 3, 4, 5, 6};
	reverse(test_a, 8, 3);
	for(int i = 0; i < 8; i++) std::cout << test_a[i] << ",";
	putchar('\n');
	reverse(test_b, 6, 2);
	for(int i = 0; i < 6; i++) std::cout << test_b[i] << ",";
	putchar('\n');
	getchar();
	return 0;
}
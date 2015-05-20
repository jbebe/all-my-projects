#include <stdio.h>
#include <stdlib.h>

double	pow_int(int a, int b);;
int		toInt(char *string);
double	toFloat(char *string);
double	Pow(int a, int b);
double	pow_int(int a, int b);
double	Abs(double a);
char	*toString(double numeric);

double toFloat(char *str){
	double	num = 0.0f,
			multiplier = 0.1f;
	unsigned char	isDecimalReached = 0,
					i;
	for (i = 0; str[i] != 0; i++){
		if (str[i]=='.'){
			isDecimalReached = 1;
			continue;
		}
		if (isDecimalReached == 0){
			num = (num*10) + (str[i]-48);
		}
		else {
			num += (str[i]-48) * multiplier;
			multiplier *= 0.1;
		}
	}
	return num;
}

int toInt(char *string){
	unsigned char	i = 0,
					sign = 0;
	int	sum = 0;
	if (string[0] == '-' && *string++ && sign++);
    while(string[i]!='\0' && string[i] > 47 && string[i] < 58)
		sum = sum*10 + (string[i++] - 48);
    return sign? -sum : sum;
}

double toFloat(char *string){
	double temp = 0;
	double sum = (double)toInt(string);
	while (*(string+1) != '\0' && *string++);
	while (*string != '.' && (temp = temp/10.0 + (double)((*string--)-48)));
	temp /= 10.0;
    return sum + temp;
}


double Pow(int a, int b){
	if (b == 0) return 1;
	if (b > 0) return a * Pow(a, b-1);
	return 1.0 / pow_int(a,-b);
}
	double pow_int(int a, int b){
		if (b == 0) return 1;
		return a * pow_int(a, b-1);
	}


double Abs(double a){
	return a > 0 ? a : -a;
}


char *toString(double numeric){
	char *output;
	unsigned char i = 0;
	unsigned char digits = 0;
	int pow10;
	double temp = numeric;
	for (; temp >= 1 && (temp /= 10); digits++);
	output = (char *)malloc((digits + 1) * sizeof(char));
	output[digits] = '\0';
	for (i = 0; i < digits; i++){
		pow10 = (int)Pow(10, digits-i-1);
		temp = (double)(numeric / pow10);
		numeric = numeric - temp * pow10;
		output[i] = (char)(temp+48);
	}
	return output;
}

double toFloat(char *str){
	double num = 0.0;
	double multiplier = 0.1;
	bool isDecimalReached = 0;
	unsigned char i;
	for (i = 0; str[i] != 0; i++){
		if (str[i]=='.'){
			isDecimalReached = 1;
			continue;
		}
		if (!isDecimalReached){
			num = (num*10) + (str[i]-'0');
		}
		else {
			num += (str[i]-'0') * multiplier;
			multiplier *= 0.1;
		}
		return num;
	}
}
#include <stdlib.h>

typedef struct string string;

struct string {
	char *text;
	unsigned int length;
	void (*add)(string*, char*);
	void (*join)(string*, string*);
};

void add(string *context, char *newstring){
	unsigned int	i,
					size_ctx = context->length + 1,
					size_news,
					full_size;
	char *temp_string;
	for(size_news = 0; newstring[size_news] != 0; size_news++);
	full_size = size_ctx + size_news;
	temp_string = (char *)malloc((full_size) * sizeof(char));
	for (i = 0; i < full_size; i++){
		if (i < size_ctx - 1) temp_string[i] = context->text[i];
		else temp_string[i] = newstring[i-size_ctx+1];
	}
	context->text = (char *)malloc(full_size * sizeof(char));
	context->text = temp_string;
	context->length = full_size;
}

void join(string *a, string *b){
	add(a,b->text);
}

string new_str(char *text){
	unsigned int i;
	string *new_string = (string *)malloc(sizeof(string));
	for(i = 0; text[i++] != 0;);
	new_string->text = (char *)malloc(i*sizeof(char));
	new_string->text = text;
	new_string->add = add;
	new_string->join = join;
	new_string->length = i - 1;
	return *new_string;
}

char *sub_toString(unsigned int i,unsigned char length){
	int shifter;
    char* p = (char *)malloc(length*sizeof(char));
    if(i<0){
        *p++ = '-';
        i = -1;
    }
    shifter = i;
    do {
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do {
        *--p = (char)((i%10)+48);
        i = i/10;
    } while(i);
    return p;
}

char *toString(double number){
	unsigned int	szamlalo = number,
					nevezo = ((number-szamlalo)*10000000),
					exp;
	char	*output,
			*szaml_str,
			*nevez_str;
	unsigned char	i = 0,
					szamlalo_digits = 0,
					nevezo_digits = 0;
	// nevezo visszaredukalasa
	while ( nevezo % 10 == 0 && ( nevezo /= 10 ));
	// elso szam hossza
	for (exp = 1; szamlalo / exp >= 1.0 && (exp *= 10); szamlalo_digits++);
	for (exp = 1; nevezo / exp >= 1.0 && (exp *= 10); nevezo_digits++);
	output = (char *)malloc((szamlalo_digits + nevezo_digits + 1) * sizeof(char));
	szaml_str = sub_toString(szamlalo,szamlalo_digits+1);
	nevez_str = sub_toString(nevezo,nevezo_digits+1);
	for (i = 0; i < szamlalo_digits + nevezo_digits; i++){
		if (i==szamlalo_digits) output[i] = '.';
		if (i < szamlalo_digits) output[i] = szaml_str[i];
		if (i > szamlalo_digits) output[i] = nevez_str[i-1-szamlalo_digits];
	}
	output[szamlalo_digits+nevezo_digits] = 0;
	return output;
}
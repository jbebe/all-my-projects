main(int i){
	char *s[]={"","fizz","buzz","banana","bumm"};
	while(i<1156)
		(printf("\n%s%s%s%s",s[i%3==0],s[(i%5==0)*2],s[(i%7==0)*3],s[(i%11==0)*4])>2||printf("%d",i))&&++i;}
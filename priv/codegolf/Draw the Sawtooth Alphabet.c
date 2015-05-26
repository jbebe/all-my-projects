/*
	A simple one today. Write the shortest program that draws 
	a "sawtooth alphabet" given a positive integer for the height. 
	You must write the name of your programming language when you come 
	to the letter it starts with.
	For example, if your language is Python and the input is 1 
	the output should be:

	ABCDEFGHIJKLMNOPythonQRSTUVWXYZ
	If the input is 2 the output should be:

	 B D F H J L N Python R T V X Z
	A C E G I K M O      Q S U W Y
	
	If the input is 4 the output should be:

	   D     J     Python     V
	  C E   I K   O      Q   U W
	 B   F H   L N        R T   X Z
	A     G     M          S     Y
*/


/*
	if n holds the height:
*/

// C + escape codes: 81
x;main(y){for(y=n--;x<26;x++)printf("\033[%d;%dH%c",n?x/n&1?y++:y--:y,x+1,x+65);}


// C 110
x;char a[702]={[0 ...701]=32};main(y){for(y=--n;x<26;a[x*27-1]=10)a[27*(n?x/n&1?y++:y--:y)+x]=x+++65;puts(a);}
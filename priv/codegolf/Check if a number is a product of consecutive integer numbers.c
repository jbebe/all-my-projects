/*
	Some numbers such as: 6, 12, 20, 30, 42, 56, 60, 90, 120 and so on as 
	can be expressed as a product of consecutive integer numbers as shown below.
	6   = 2 * 3  
	12  = 3 * 4  
	30  = 5 * 6
	60  = 3 * 4 * 5  
	90  = 9 * 10  
	120 = 4 * 5 * 6  
	Write a program or function that outputs a list of consecutive integers 
	which product equals the specified number.
*/

/*
	C 105
*/

n,k,l;main(i){for(scanf("%d",&n);++i<n;)for(k=1,l=i;k<n;)if(k*=l++,k==n)for(l=n;l/=i;)printf("%d ",i++);}

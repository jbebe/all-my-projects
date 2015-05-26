/*
	Write a program that outputs all 64 layers of this representation 
	of Graham's number
*/


// C 161

main(i){for(char d[]={[0 ...126]=46,i=0},l[]={[0 ...62]=95,0};i<63;)printf("3^^%s^3\n%*s\\%s  %s/\n%*s\n%*s",d+2*i++,i,"",l+i,l+i,67,"\\/",i,"");puts("3^^^^3");}

// JS

r="repeat";o="";u="_";s=" ";(f=i=>i?"3^^"+"."[r](i*2+1)+"^3\n"+s[r](64-i)+"\\"+u[r](i)+s[r](2)+u[r](i)+"/\n"+s[r](65)+"\\/\n"+s[r](64-i)+f(i-1):"3^^^^3")(63);

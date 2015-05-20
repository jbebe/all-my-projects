#include <stdio.h>
//int main(int l){char h=-1,*c="\\/";scanf("%d",&l);while(h++<l*2)printf("%*c%*c\n",h-2*(h/l)*(h%l)-h/l+1,c[h/l],2*(l-h)+4*(h/l)*(h%l)+2*(h/l)-1,c[1-h/l]);return 0;}

main(                int l
  ){char            h=-1,*
   c="\\"          "/";
    scanf        ("%d"
     ,&l);      while
       (h++<   l*2)
          printf(
        "%*c%*c\n"
       ,h-2*(h/l)*(
      h%l)-h   /l+1,c
    [h/l],      2*(l-h
   )+4*(h        /l)*(h
  %l)+2*          (h/l)-
 1,c[1-            h/l]);}

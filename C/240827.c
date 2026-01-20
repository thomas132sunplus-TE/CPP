#include<stdio.h>

int main(){

    int i,j,k;
    float x,y;
    char str1[10],str2[4];

    sscanf("252 54.32E-1 Thompson 56789 123 ab56789",
            "%d %f %9s %2d %f %d %3s[0-9]", 
             &i, &x, str1, &j, &y, &k,str2
    );

    printf("%d %f %9s %2d %f %d %s", i,x,str1,j,y,k,str2 );

}
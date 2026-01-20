#include<stdio.h>
int main(){
    
    float n = 100; 
    float *p = &n ;

    *p = 10;
     n = 100;
     printf(" n value is %f\n",n);
     printf(" p value is %p\n",p);
     printf("*p value is %f\n",*p);
}
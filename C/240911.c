#include<stdio.h>

int main(void){

    double n = 10;
    double *p = &n;
    
    printf("n  = %f\n",*p);
    printf("p 的位置  : = %p\n",p);
    printf("p + 1    : = %p\n",p+1);
    printf("p + 2    : = %p\n",p+2);

    printf("\n");
    printf("when p=0 \n");
    p = 0;
    
    printf("p 的位置 : = %p\n",p);
    printf("p + 1    : = %p\n",p+1);
    printf("p + 2    : = %p\n",p+2);
    printf("n  = %f\n",n);

    p = &n;

    printf("n  = %f\n",*p);
    printf("n  = %p\n",p);
     
    return 0; 

}
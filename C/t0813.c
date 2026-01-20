#include<stdio.h>

int main(){

    int n = 10;
    int *p = &n;
    
    printf(" n 的值 = %d\n" , n);
    printf(" n 的位置 = %p\n" , &n);
    *p=16;
    printf(" n 的值 = %d\n" , n);
    printf(" p 儲存n的位置 = %p\n" ,  p);
    printf("*p 儲存n的值   = %d\n" , *p); 
    
        
}


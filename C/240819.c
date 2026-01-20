#include<stdio.h>

int main(){
    const int n = 10;
          int *p = &n;
    *p = 20;
    printf("%p\n",p);
    printf("%d\n",*p);
    
       
}
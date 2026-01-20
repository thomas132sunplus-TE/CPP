#include<stdio.h>
int main(){

    int n = 10;
    void *p=&n;

    // printf("*p value is %p\",*p);

    int *iptr = (int*) p;
    printf("%d\n",*iptr);
    printf("p value is %d\n", p);

}
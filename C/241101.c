#include<stdio.h>

int main(){
    int n = 10;
    int *p1 = &n;
    int **p2 = &p1;

    printf("n 的值 =  %d\n",n);
    printf("n 的位置 : %p\n",p1);
    printf("p1 的位置 : %p\n",p2);

    return 0;

}
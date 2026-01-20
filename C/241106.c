#include<stdio.h>

int main(){
    int arr[1][2][3] = {{{1,2,3},{4,5,6}}};
    int (*p)[2][3] = arr;

    printf("arr ¦ì¸m :%p\n",arr);
    printf("arr ¦ì¸m :%p\n",p);
    printf("arr ¦ì¸m :%p\n",*p);
}
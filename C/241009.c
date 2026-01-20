#include<stdio.h>
#define LEN 5

int main(void){
    int arr[] = {10,20,30,40,50};
    //int len = *(&arr+1)-arr;
    //int (*p)[5] = &arr;

    printf("arr = %p \n",arr);
    printf("&arr = %p \n",&arr);
    printf("(&arr+1)+1 = %p \n",(&arr+1)+1);
    printf("len = %d \n",*(&arr+1)-arr);
}
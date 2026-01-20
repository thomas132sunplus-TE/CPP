#include<stdio.h>

int main(){
    int arr[] = {10,20,30,40,50,60,70,80};
    int *begin = arr;
    int *end = *(&arr+1);
   
    printf("end = %p\n",end);
    printf("begin = %p\n",begin);
    printf("arr length = %d\n",end-begin);
}
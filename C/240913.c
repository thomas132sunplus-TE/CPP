#include<stdio.h>
#define LEN 20

int main(void){
    int arr[LEN]={0};
    int *ptr = arr;

    for (int i = 0; i < LEN ; i++){
        printf("&arr[%d] = %p",i,&arr[i]);
        printf("\t\t ptr + %d : %p\n",i,ptr+i);
    }
}

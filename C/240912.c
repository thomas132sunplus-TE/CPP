#include<stdio.h>

int main(void){
    int arr[100] = {0};

    printf("arr+1 =\t%p\n",arr+1);
    printf("arr[0]=\t%p\n",&arr[1]);

    for (int i=0;i<100;i++){
        arr[i]=i;
        printf("%d\t",arr[i]);
    }

    return 0;
}
#include<stdio.h>

int main(void){

    int number[]={0,1,2,3,4};
    int length = sizeof(number)/sizeof(number[1]);

    printf("length = %d\n",length );

    for (int i=0; i<length ; i++) {
        printf("%d  ",number[i]);
    }
    return 0;
}

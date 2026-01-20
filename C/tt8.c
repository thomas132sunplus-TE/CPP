#include<stdio.h>

int main(void){
    int num=75;
    printf("the anser is : %d\n",num > 70 && num < 80);
    printf("%d\n",num > 80 || num < 75);
    printf("%d\n",!(num > 80 || num < 75));

}